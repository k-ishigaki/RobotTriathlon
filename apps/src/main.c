/*
 * ロボットトライアスロン用のプログラム
 * とりあえずLチカ
 */

#include <xc.h>
#include <stdbool.h>
// Hardwareモジュールのインクルード
#include "Hardware.h"
#include "SerialPort.h"

#define _XTAL_FREQ 64000000L

// function prototype
void setup(void);
void loop(void);

// instance of Object
DigitalOutputPin* led;
DigitalOutputPin* led2;
SerialPort* serial;
TimerModule* timer;


static uint16_t onTimerInterrupt() {
	static long periodCount = 10000;
	static long dutyCount = 5000;
	bool value = led2->getValue();

	// 擬似的にPWMを発生させる
	if (value == false) {
		led2->setValue(true);
		return dutyCount;
	} else {
		long previousDutyCount = dutyCount;

		led2->setValue(false);
		dutyCount -= 5;
		if (dutyCount < 10) {
			dutyCount = 5000;
		}
		return periodCount - previousDutyCount;
	}
}

static PeriodicInterruptListener listener = {
	onTimerInterrupt,
};

int main(void) {
	setup();
	while (true) {
		loop();
	}
}

void setup() {
	// Oscillator settings
	OscillatorModule* osc = getOscillatorModule();
	osc->getPhaseLockedLoop()->enablePLL();
	osc->getInternalOscillator()->setFrequency(16000000L);
	osc->selectSystemClock(PRIMARY);
	// LED Pin settings
	led = getRA0()->getDigitalOutputPin();
	led2 = getRA1()->getDigitalOutputPin();
	// Serial Port settings
	serial = getSerialPort(
			getRC7()->getDigitalPin(),
			getRC6()->getDigitalPin(),
			getEUSART1(),
			115200);
	// Timer settings
	// テストとして約30Hzで割り込みさせる
	timer = getTimer1(
			SIXTEEN_BIT_TIMER_CLOCKSOURCE_INSTRUCTION_CLOCK,
			SIXTEEN_BIT_TIMER_PRISCALER_1_8);
	timer->getPeriodicInterruptController()->addInterruptListener(&listener);
	timer->getPeriodicInterruptController()->enableInterrupt(LOW_PRIORITY);
	timer->getPeriodicInterruptController()->setPeriodCount(65536);
	timer->start();
	// interrupt settings
	RCONbits.IPEN = 1;
	INTCONbits.GIEL = 1;
	INTCONbits.GIEH = 1;
}

void interrupt high_priority isr_high() {
	// do nothing
}

void interrupt low_priority isr_low() {
	EUSART1_handleInterrupt();
	Timer1_handleInterrupt();
}

void loop() {
	bool value;

	value = !led->getValue();
	led->setValue(value);
	for (unsigned char i=0; i<100; i++) {
		__delay_ms(10);
	}
	uint8_t data = serial->getByteInputStream()->read();
	while (data != 0) {
		serial->getByteOutputStream()->write(data);
		data = serial->getByteInputStream()->read();
	}
}

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
TimerModule* timer1;
ECCPModule* ccp1;

static uint16_t onCompareMatched() {
	static long dutyCount = 0xFFF0;

	dutyCount -= 100;
	if (dutyCount < 100) {
		dutyCount = 0xFFF0;
	}
	led2->setValue(false);
	return dutyCount;
}

static CompareMatchInterruptListener cmListener = {
	onCompareMatched,
};

static uint16_t onTimerInterrupt() {
	led2->setValue(true);
	return 0;
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
	timer1 = getTimer1(
			SIXTEEN_BIT_TIMER_CLOCKSOURCE_INSTRUCTION_CLOCK,
			SIXTEEN_BIT_TIMER_PRISCALER_1_1);
	timer1->getPeriodicInterruptController()->addInterruptListener(&listener);
	timer1->getPeriodicInterruptController()->enableInterrupt(LOW_PRIORITY);
	timer1->getPeriodicInterruptController()->setPeriodCount(0xFFFF);
	timer1->start();
	// CCP settings
	ccp1 = getECCP1(ECCP_MODULE_TIMR_SOURCE_TIMER1_TIMER2);
	ccp1->getCompareMatchInterruptController()->setCompareMatchCount(0xFFFF);
	ccp1->getCompareMatchInterruptController()->addCompareMatchInterruptListener(&cmListener);
	ccp1->getCompareMatchInterruptController()->enableCompareMatchInterrupt(HIGH_PRIORITY);
	// interrupt settings
	RCONbits.IPEN = 1;
	INTCONbits.GIEL = 1;
	INTCONbits.GIEH = 1;
}

void interrupt high_priority isr_high() {
	ECCP1_handleInterrupt();
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

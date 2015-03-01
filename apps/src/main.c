/*
 * ロボットトライアスロン用のプログラム
 * とりあえずLチカ
 */

#include <xc.h>
#include <stdbool.h>
// Hardwareモジュールのインクルード
#include "Hardware.h"
#include "SerialPort.h"
#include "MotorDriver.h"

#define _XTAL_FREQ 64000000L

// function prototype
void setup(void);
void setupMotorDriver(void);
void loop(void);

// instance of Object
DigitalOutputPin* led;
SerialPort* serial;

MotorDriver* leftMotor;
MotorDriver* rightMotor;

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
	osc->getInternalOscillator()->setFrequency(_XTAL_FREQ/4);
	osc->selectSystemClock(PRIMARY);
	// LED Pin settings
	led = getRA0()->getDigitalOutputPin();
	// Serial Port settings
	serial = getSerialPort(
			getRC7()->getDigitalPin(),
			getRC6()->getDigitalPin(),
			getEUSART1(),
			115200);
	// gpio port settings

	// initilize left motor
	GPIOPort* portB = getPORTB();
	portB->setDigitalOutput(0x0F);
	TimerModule* timer3 = getTimer3(
			SIXTEEN_BIT_TIMER_CLOCKSOURCE_INSTRUCTION_CLOCK,
			SIXTEEN_BIT_TIMER_PRISCALER_1_1);
	timer3->start();
	leftMotor = getLeftMotor(
			timer3->getPeriodicInterruptController(),
			getECCP2(ECCP_MODULE_TIMR_SOURCE_TIMER3_TIMER4)->getCompareMatchInterruptController(),
			portB,
			0x0F,
			0x00, 0xFF, 0x0F, 0x00);
	leftMotor->setForward();
	// initilize right motor
	portB->setDigitalOutput(0xF0);
	rightMotor = getRightMotor(
			timer3->getPeriodicInterruptController(),
			getECCP3(ECCP_MODULE_TIMR_SOURCE_TIMER3_TIMER4)->getCompareMatchInterruptController(),
			portB,
			0xF0,
			0x00, 0xFF, 0x0F, 0x00);
	rightMotor->setForward();

	// interrupt settings
	RCONbits.IPEN = 1;
	INTCONbits.GIEL = 1;
	INTCONbits.GIEH = 1;
}

void interrupt high_priority isr_high() {
	Timer3_handleInterrupt();
	ECCP2_handleInterrupt();
	ECCP3_handleInterrupt();
}

void interrupt low_priority isr_low() {
	EUSART1_handleInterrupt();
}

void loop() {
	bool value = led->getValue();
	led->setValue(!value);
	if (value == true) {
		leftMotor->setPWMDutyValue(1000);
		rightMotor->setPWMDutyValue(1000);
	} else {
		leftMotor->setPWMDutyValue(100);
		rightMotor->setPWMDutyValue(100);
	}
	for (unsigned char i=0; i<100; i++) {
		__delay_ms(10);
	}
	uint8_t data = serial->getByteInputStream()->read();
	while (data != 0) {
		serial->getByteOutputStream()->write(data);
		data = serial->getByteInputStream()->read();
	}
}

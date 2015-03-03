/*
 * ロボットトライアスロン用のプログラム
 * とりあえずLチカ
 */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Hardwareモジュールのインクルード
#include "Hardware.h"
#include "SerialPort.h"
#include "MotorDriver.h"
#include "SpeedCounter.h"
#include "MotionController.h"
#include "LineSensor.h"

#define _XTAL_FREQ 64000000L

// function prototype
void setup(void);
void setupMotorDriver(void);
void loop(void);

// instance of Object
DigitalOutputPin* led;
DigitalOutputPin* led2;
SerialPort* serial;

MotorDriver* leftMotor;
MotorDriver* rightMotor;

SpeedCounter* leftSpeedCounter;
SpeedCounter* rightSpeedCounter;

MotionController* motionController;

I2CInterface* i2c;
LineSensor* lineSensor;

/**
 * LEDを光らせるための周期割り込みリスナ
 */
static uint16_t onTimerOverflowed() {
	bool value = led2->getValue();
	led2->setValue(!value);
	return 0;
}

static PeriodicInterruptListener ledBlinkListener = {
	onTimerOverflowed,
};

void putch(char data) {
	serial->getByteOutputStream()->write(data);
}

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
	led = getRA2()->getDigitalOutputPin();
	led2 = getRA3()->getDigitalOutputPin();
	// Serial Port settings
	serial = getSerialPort(
			getRB7()->getDigitalPin(),
			getRB6()->getDigitalPin(),
			getEUSART2(),
			115200);
	// gpio port settings

	// initilize left motor
	GPIOPort* portC = getPORTC();
	portC->setDigitalOutput(0xFF);
	TimerModule* timer3 = getTimer3(
			SIXTEEN_BIT_TIMER_CLOCKSOURCE_INSTRUCTION_CLOCK,
			SIXTEEN_BIT_TIMER_PRISCALER_1_1);
	timer3->start();
	leftMotor = getLeftMotor(
			timer3->getPeriodicInterruptController(),
			getECCP2(ECCP_MODULE_TIMR_SOURCE_TIMER3_TIMER4)->getCompareMatchInterruptController(),
			portC,
			0x0F,
			0x00, 0xFF, 0x0F, 0x00);
	leftMotor->setForward();
	// initilize right motor
	rightMotor = getRightMotor(
			timer3->getPeriodicInterruptController(),
			getECCP3(ECCP_MODULE_TIMR_SOURCE_TIMER3_TIMER4)->getCompareMatchInterruptController(),
			portC,
			0xF0,
			0x00, 0xFF, 0x0F, 0x00);
	rightMotor->setForward();

	// initilize encorder
	VREFCON1bits.DACEN = 1; // DAC enabled
	VREFCON1bits.DACLPS = 0; // DAC Negative reference source
	VREFCON1bits.DACOE = 0; // disconnected from the DACOUT pin
	VREFCON1bits.DACPSS = 0b00; // VDD is positive ref
	VREFCON1bits.DACNSS = 0; // VSS is negative ref
	VREFCON2bits.DACR = 16; // ~2.5V

	AnalogPin* ra0 = getRA0()->getAnalogPin();
	ra0->setDirection(false);
	ComparatorModule* comparator1 = getComparator1(
			COMPARATOR_MODULE_REFERENCE_DAC,
			COMPARATOR_MODULE_HYSTERESIS_ENABLE,
			COMPARATOR_MODULE_SYNCHRONOUS_MODE_ASYNCHRONOUS);
	comparator1->selectComparatorChannel(COMPARATOR_MODULE_CHANNEL_C12IN0);
	TimerModule* timer1 = getTimer1(
			SIXTEEN_BIT_TIMER_CLOCKSOURCE_INSTRUCTION_CLOCK,
			SIXTEEN_BIT_TIMER_PRISCALER_1_8);
	timer1->start();
	leftSpeedCounter = getLeftSpeedCounter(
			comparator1,
			timer1->getPeriodicInterruptController());
	AnalogPin* ra1 = getRA1()->getAnalogPin();
	ra1->setDirection(false);
	ComparatorModule* comparator2 = getComparator2(
			COMPARATOR_MODULE_REFERENCE_DAC,
			COMPARATOR_MODULE_HYSTERESIS_ENABLE,
			COMPARATOR_MODULE_SYNCHRONOUS_MODE_ASYNCHRONOUS);
	comparator2->selectComparatorChannel(COMPARATOR_MODULE_CHANNEL_C12IN1);
	rightSpeedCounter = getRightSpeedCounter(
			comparator2,
			timer1->getPeriodicInterruptController());

	TimerModule* timer5 = getTimer5(
			SIXTEEN_BIT_TIMER_CLOCKSOURCE_INSTRUCTION_CLOCK,
			SIXTEEN_BIT_TIMER_PRISCALER_1_8);
	timer5->start();
	motionController = getMotionController(
			timer5->getPeriodicInterruptController(),
			leftMotor,
			leftSpeedCounter,
			rightMotor,
			rightSpeedCounter);
	motionController->moveStraight(50);

	// initilize i2c
	i2c = getMSSP2(getRB2()->getDigitalPin(), getRB1()->getDigitalPin())->getI2CInterface();
	// initilize line sensor
	lineSensor = getLineSensor(i2c);

	// add led blink task
	TimerModule* timer2 = getTimer2(EIGHT_BIT_TIMER_PRISCALER_1_16, EIGHT_BIT_TIMER_POSTSCALER_1_16);
	timer2->getPeriodicInterruptController()->addInterruptListener(&ledBlinkListener);
	timer2->getPeriodicInterruptController()->enableInterrupt(LOW_PRIORITY);
	timer2->start();

	


	// interrupt settings
	RCONbits.IPEN = 1;
	INTCONbits.GIEL = 1;
	INTCONbits.GIEH = 1;
}

void interrupt high_priority isr_high() {
	Timer1_handleInterrupt();
	Timer3_handleInterrupt();
	ECCP2_handleInterrupt();
	ECCP3_handleInterrupt();
	Comparator1_handleInterrupt();
	Comparator2_handleInterrupt();
}

void interrupt low_priority isr_low() {
	Timer5_handleInterrupt();
	Timer2_handleInterrupt();
	EUSART2_handleInterrupt();
}

void loop() {
	bool value = led->getValue();
	led->setValue(!value);
	printf("lineValue = %05d\tspeed = %05d\r\n", lineSensor->getLineValue(), leftSpeedCounter->getSpeedCount());
	for (unsigned char i=0; i<10; i++) {
		__delay_ms(10);
	}
	uint8_t data = serial->getByteInputStream()->read();
	while (data != 0) {
		serial->getByteOutputStream()->write(data);
		data = serial->getByteInputStream()->read();
	}
}

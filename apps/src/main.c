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
#include "PWMOutputter.h"
#include "TimeIntervalCounter.h"
#include "TaskManager.h"
#include "DistanceSensor.h"

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

SpeedCounter* leftSpeedCounter;
SpeedCounter* rightSpeedCounter;

MotionController* motionController;

LineSensor* lineSensor;

DistanceSensor* leftDistanceSensor;
DistanceSensor* rightDistanceSensor;

/**
 * LEDを光らせるための周期割り込みリスナ
 */
static uint16_t onTimerOverflowed() {
	static char count = 0;
	count++;
	if (count > 100) {
		count = 0;
		bool value = led->getValue();
		led->setValue(!value);
	}
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
	// Serial Port settings
	serial = getSerialPort(
			getRC7()->getDigitalPin(),
			getRC6()->getDigitalPin(),
			getEUSART1(),
			115200);
	// gpio port settings

	// initilize left motor
	GPIOPort* portA = getPORTA();
	portA->setDigitalOutput(0xF0);
	TimerModule* timer3 = getTimer3(
			SIXTEEN_BIT_TIMER_CLOCKSOURCE_INSTRUCTION_CLOCK,
			SIXTEEN_BIT_TIMER_PRISCALER_1_1);
	timer3->start();
	leftMotor = getLeftMotor(
			timer3->getPeriodicInterruptController(),
			getCCP4(ECCP_MODULE_TIMR_SOURCE_TIMER3_TIMER4)->getCompareMatchInterruptController(),
			portA,
			0b11000000,
			0x00, 0xFF, 0x0F, 0x00);
	leftMotor->setForward();
	// initilize right motor
	rightMotor = getRightMotor(
			timer3->getPeriodicInterruptController(),
			getCCP5(ECCP_MODULE_TIMR_SOURCE_TIMER3_TIMER4)->getCompareMatchInterruptController(),
			portA,
			0b00110000,
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

	TimerModule* timer6 = getTimer6(EIGHT_BIT_TIMER_PRISCALER_1_16, EIGHT_BIT_TIMER_POSTSCALER_1_16);
	timer6->start();
	motionController = getMotionController(
			timer6->getPeriodicInterruptController(),
			leftMotor,
			leftSpeedCounter,
			rightMotor,
			rightSpeedCounter);
	motionController->moveStraight(50);

	// initilize line sensor
	I2CInterface* i2c = getMSSP1(getRC4()->getDigitalPin(), getRC3()->getDigitalPin())->getI2CInterface();
	lineSensor = getLineSensor(i2c);

	// add led blink task
	TimerModule* timer2 = getTimer2(EIGHT_BIT_TIMER_PRISCALER_1_16, EIGHT_BIT_TIMER_POSTSCALER_1_16);
	timer2->getPeriodicInterruptController()->addInterruptListener(&ledBlinkListener);
	timer2->getPeriodicInterruptController()->enableInterrupt(LOW_PRIORITY);
	timer2->start();
	
	// initilize distance sensor
	TimerModule* timer4 = getTimer4(
			EIGHT_BIT_TIMER_PRISCALER_1_4,
			EIGHT_BIT_TIMER_POSTSCALER_1_16);
	
	TimerModule* timer5 = getTimer5(
			SIXTEEN_BIT_TIMER_CLOCKSOURCE_INSTRUCTION_CLOCK,
			SIXTEEN_BIT_TIMER_PRISCALER_1_8);
	DigitalPin* rb5 = getRB5()->getDigitalPin();
	InputCaptureController* inputCaptureController = getECCP3(
			ECCP_MODULE_TIMR_SOURCE_TIMER3_TIMER4)->getInputCaptureController();

	leftDistanceSensor = getDistanceSensor2(
			getPWMOutputter2(
				getRC0()->getDigitalPin(),
				getRC1()->getDigitalPin(),
				getECCP2(ECCP_MODULE_TIMR_SOURCE_TIMER3_TIMER4)->getEnhancedPWMDriver()),
			getTimeIntervalCounter2(
				timer5,
				rb5,
				inputCaptureController),
			getTaskManger2(
				timer4->getPeriodicInterruptController()));

	rightDistanceSensor = getDistanceSensor1(
			getPWMOutputter1(
				getRC2()->getDigitalPin(),
				getRB2()->getDigitalPin(),
				getECCP1(ECCP_MODULE_TIMR_SOURCE_TIMER3_TIMER4)->getEnhancedPWMDriver()),
			getTimeIntervalCounter1(
				timer5,
				rb5,
				inputCaptureController),
			getTaskManger2(
				timer4->getPeriodicInterruptController()));

	timer4->getPeriodicInterruptController()->setPeriodCount(100);	// 40kHz
	timer4->start();




	// interrupt settings
	RCONbits.IPEN = 1;
	INTCONbits.GIEL = 1;
	INTCONbits.GIEH = 1;
}

void interrupt high_priority isr_high() {
	Timer1_handleInterrupt();
	Timer3_handleInterrupt();
	CCP4_handleInterrupt();
	CCP5_handleInterrupt();
	Comparator1_handleInterrupt();
	Comparator2_handleInterrupt();
}

void interrupt low_priority isr_low() {
	Timer2_handleInterrupt();
	Timer4_handleInterrupt();
	Timer6_handleInterrupt();
	ECCP3_handleInterrupt();
	EUSART1_handleInterrupt();
}

void loop() {
	static uint8_t count = 0;
	count++;
	//printf("coun = %05d\tline = %05d\tspee = %05d\r\n", count, lineSensor->getLineValue(), leftSpeedCounter->getSpeedCount());
	printf("coun =%05d\tline = %05d\tspee = %05d\tdist = %05d\r\n", count, lineSensor->getLineValue(), leftSpeedCounter->getSpeedCount(), leftDistanceSensor->getDistaneCount());
	for (unsigned char i=0; i<100; i++) {
		__delay_ms(10);
	}
}

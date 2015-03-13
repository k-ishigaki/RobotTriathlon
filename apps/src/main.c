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

#define KP 8
#define KD 4

// function prototype
void setup(void);
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

void putch(char data) {
	serial->getByteOutputStream()->write(data);
}

bool onLineTraceTaskCalled() {
	static uint16_t waitCount = 0;
	static uint8_t interruptCounter = 0;
	if (interruptCounter < 4) {
		interruptCounter++;
		return true;
	} else {
		interruptCounter = 0;
	}
	if (waitCount > 0) {
		waitCount--;
		return true;
	}

	LineState lineState = lineSensor->getLineState();
	if (lineState == LINE_STATE_ON_LINE) {
		/** 前回の位置偏差（微分項算出に使用） */
		static int previousDeflection;
		// 偏差の取得
		int deflection = lineSensor->getLineValue();
		// 比例項の計算
		int proportional = KP * deflection;
		// 微分項の計算
		int derivative = KD * (deflection - previousDeflection);
		// 曲率半径の逆数の計算
		// 初期値代入
		int r_inverse = 0;
		// 比例項
		r_inverse += proportional;
		// 微分項
		r_inverse += derivative;
		// 変換式
		r_inverse = r_inverse >> 9;
		// 適用
		motionController->moveCorner(70, r_inverse);
	} else if (lineState == LINE_STATE_LEFT_EDGE_DITECTED) {
		motionController->moveCorner(20, -46);
		waitCount = 1000;
	} else if (lineState == LINE_STATE_RIGHT_EDGE_DITECTED) {
		motionController->moveCorner(20, 46);
		waitCount = 1000;
	} else if (lineState == LINE_STATE_BOTH_EDGE_DITECTED) {
		motionController->stop();
		return true;
	}
	return true;
}

PeriodicCalledTask lineTraceTask = {
	onLineTraceTaskCalled,
};

bool onObstacleTaskCalled() {
	static uint8_t interruptCounter = 0;
	if (interruptCounter < 4) {
		interruptCounter++;
		return true;
	} else {
		interruptCounter = 0;
	}
	int lineState = lineSensor->getLineState();
	while (lineState != LINE_STATE_ON_LINE) {
		int distanceCount = leftDistanceSensor->getDistaneCount();
		motionController->stop();
		for (uint16_t i=0; i<200; i++) {
			if (lineSensor->getLineState() == LINE_STATE_ON_LINE) {
				break;
			}
			__delay_ms(1);
		}
		motionController->moveCorner(10, -46);
		for (uint16_t i=0; i<200; i++) {
			if (lineSensor->getLineState() == LINE_STATE_ON_LINE) {
				break;
			}
			__delay_ms(1);
		}
		motionController->stop();
		for (uint16_t i=0; i<200; i++) {
			if (lineSensor->getLineState() == LINE_STATE_ON_LINE) {
				break;
			}
			__delay_ms(1);
		}
		motionController->moveCorner(10, 0);
		for (uint16_t i=0; i<200; i++) {
			if (lineSensor->getLineState() == LINE_STATE_ON_LINE) {
				break;
			}
			__delay_ms(1);
		}
		motionController->stop();
		for (uint16_t i=0; i<200; i++) {
			if (lineSensor->getLineState() == LINE_STATE_ON_LINE) {
				break;
			}
			__delay_ms(1);
		}
		motionController->moveCorner(10, 46);
		for (uint16_t i=0; i<200; i++) {
			if (lineSensor->getLineState() == LINE_STATE_ON_LINE) {
				break;
			}
			__delay_ms(1);
		}
	}
	return false;
}

PeriodicCalledTask obstacleTask = {
	onObstacleTaskCalled,
};

bool onCurveTaskCalled() {
	while (lineSensor->getLineState() == LINE_STATE_ON_LINE) {
		motionController->moveStraight(-20);
	}
	while (lineSensor->getLineState() == LINE_STATE_ON_LINE) {
		motionController->moveCorner(20, 23);
	}
	return false;
}

PeriodicCalledTask curveTask = {
	onCurveTaskCalled,
};


bool onStopTaskCalled() {
	motionController->moveStraight(10);
	return true;
}

PeriodicCalledTask stopTask = {
	onStopTaskCalled,
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
	osc->getInternalOscillator()->setFrequency(_XTAL_FREQ/4);
	osc->selectSystemClock(PRIMARY);
	// Serial Port settings
	serial = getSerialPort(
			getRC7()->getDigitalPin(),
			getRC6()->getDigitalPin(),
			getEUSART1(),
			115200);
	// gpio port settings

	// initilize left motor
	GPIOPort* portA = getPORTA();
	portA->setDigitalOutput(0xFF);
	TimerModule* timer3 = getTimer3(
			SIXTEEN_BIT_TIMER_CLOCKSOURCE_INSTRUCTION_CLOCK,
			SIXTEEN_BIT_TIMER_PRISCALER_1_1);
	timer3->start();
	leftMotor = getLeftMotor(
			timer3->getPeriodicInterruptController(),
			getCCP4(ECCP_MODULE_TIMR_SOURCE_TIMER3_TIMER4)->getCompareMatchInterruptController(),
			portA,
			0b00001111,
			0b00000010, 0b00000110, 0b00001001, 0b00000101);
	leftMotor->setForward();
	// initilize right motor
	rightMotor = getRightMotor(
			timer3->getPeriodicInterruptController(),
			getCCP5(ECCP_MODULE_TIMR_SOURCE_TIMER3_TIMER4)->getCompareMatchInterruptController(),
			portA,
			0b11110000,
			0b00100000, 0b10100000, 0b01010000, 0b10010000);
	rightMotor->setForward();

	// initilize encorder
	VREFCON1bits.DACEN = 1; // DAC enabled
	VREFCON1bits.DACLPS = 0; // DAC Negative reference source
	VREFCON1bits.DACOE = 0; // disconnected from the DACOUT pin
	VREFCON1bits.DACPSS = 0b00; // VDD is positive ref
	VREFCON1bits.DACNSS = 0; // VSS is negative ref
	VREFCON2bits.DACR = 16; // ~2.5V

	AnalogPin* rb3 = getRB3()->getAnalogPin();
	rb3->setDirection(false);
	ComparatorModule* comparator1 = getComparator1(
			COMPARATOR_MODULE_REFERENCE_DAC,
			COMPARATOR_MODULE_HYSTERESIS_ENABLE,
			COMPARATOR_MODULE_SYNCHRONOUS_MODE_ASYNCHRONOUS);
	comparator1->selectComparatorChannel(COMPARATOR_MODULE_CHANNEL_C12IN2);
	TimerModule* timer1 = getTimer1(
			SIXTEEN_BIT_TIMER_CLOCKSOURCE_INSTRUCTION_CLOCK,
			SIXTEEN_BIT_TIMER_PRISCALER_1_8);
	timer1->start();
	leftSpeedCounter = getLeftSpeedCounter(
			comparator1,
			timer1->getPeriodicInterruptController());
	AnalogPin* rb1 = getRB1()->getAnalogPin();
	rb1->setDirection(false);
	ComparatorModule* comparator2 = getComparator2(
			COMPARATOR_MODULE_REFERENCE_DAC,
			COMPARATOR_MODULE_HYSTERESIS_ENABLE,
			COMPARATOR_MODULE_SYNCHRONOUS_MODE_ASYNCHRONOUS);
	comparator2->selectComparatorChannel(COMPARATOR_MODULE_CHANNEL_C12IN3);
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

	// initilize distance sensor
	TimerModule* timer4 = getTimer4(
			EIGHT_BIT_TIMER_PRISCALER_1_4,
			EIGHT_BIT_TIMER_POSTSCALER_1_16);
	
	TimerModule* timer5 = getTimer5(
			SIXTEEN_BIT_TIMER_CLOCKSOURCE_INSTRUCTION_CLOCK,
			SIXTEEN_BIT_TIMER_PRISCALER_1_8);
	DigitalPin* rb5 = getRB5()->getDigitalPin();
	InputCaptureController* inputCaptureController = getECCP3(
			ECCP_MODULE_TIMR_SOURCE_TIMER5_TIMER6)->getInputCaptureController();

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

	// initilize main task
	TimerModule* timer2 = getTimer2(
			EIGHT_BIT_TIMER_PRISCALER_1_16,
			EIGHT_BIT_TIMER_POSTSCALER_1_16);
	TaskManager* mainTaskManager = getTaskManger1(
			timer2->getPeriodicInterruptController());
	mainTaskManager->addPeriodicCalledTack(&lineTraceTask);
	//mainTaskManager->addPeriodicCalledTack(&obstacleTask);
	//mainTaskManager->addPeriodicCalledTack(&curveTask);
	//mainTaskManager->addPeriodicCalledTack(&lineTraceTask);
	//mainTaskManager->addPeriodicCalledTack(&stopTask);
	mainTaskManager->enableTaskInterrupt();
	timer2->start();


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
	motionController->moveCorner(10, 46);
	//static uint8_t count = 0;
	//count++;
	////printf("coun = %05d\tline = %05d\tspee = %05d\r\n", count, lineSensor->getLineValue(), leftSpeedCounter->getSpeedCount());
	//printf("count =%05d\t", count);
	//printf("linev = %05d\t", lineSensor->getLineValue());
	//printf("spel = %05d\t", leftSpeedCounter->getSpeedCount());
	//printf("sper = %05d\t\r\n", rightSpeedCounter->getSpeedCount());
	//printf("distL = %05d\t", leftDistanceSensor->getDistaneCount());
	//printf("distR = %05d\r\n", rightDistanceSensor->getDistaneCount());
	//printf("\r\n");
	//for (unsigned char i=0; i<10; i++) {
	//	__delay_ms(10);
	//}
}


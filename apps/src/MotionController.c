#include "MotionController.h"

#include <stdio.h>

#define MAXIMUM_PWM_DUTY_VALUE 1000
#define KP 20
#define KI 800
#define KD 0

#define NAMESPACE(name) MotionController_##name
#define MotionController_getter getMotionController

// common variables
MotorDriver* NAMESPACE(leftMotorDriver);
SpeedCounter* NAMESPACE(leftSpeedCounter);
MotorDriver* NAMESPACE(rightMotorDriver);
SpeedCounter* NAMESPACE(rightSpeedCounter);
/**
 * 目標速度（カウント基準）
 * 計算しやすいようにするためintで宣言
 */
int NAMESPACE(leftTarget);
int NAMESPACE(rightTarget);

// --------------------------------------------------------------------
// PeriodicInterruptListener
// --------------------------------------------------------------------
// field methods
static uint16_t NAMESPACE(onTimerOverflowed)() {
	/** 前回の速度偏差（微分項算出に使用） */
	static int previousLeftDeflection;
	static int previousRightDeflection;
	/** 偏差の積分値（積分項算出に使用 */
	static long integratedLeftDeflection;
	static long integratedRightDeflection;
	// スピードの取得
	int left = NAMESPACE(leftSpeedCounter)->getSpeedCount();
	int right = NAMESPACE(rightSpeedCounter)->getSpeedCount();
	// 偏差の計算
	int leftDeflection = NAMESPACE(leftTarget) - left;
	int rightDeflection = NAMESPACE(rightTarget) - right;
	// 比例項の計算
	int leftProportional = KP * leftDeflection;
	int rightProportional = KP * rightDeflection;
	leftProportional = leftProportional > 1000 ? 1000 : leftProportional;
	rightProportional = rightProportional > 1000 ? 1000 : rightProportional;
	// 積分項の計算
	integratedLeftDeflection += KI * leftDeflection;
	integratedRightDeflection += KI * rightDeflection;
	integratedLeftDeflection = integratedLeftDeflection < 0 ? 0 : integratedLeftDeflection;
	integratedRightDeflection = integratedRightDeflection < 0 ? 0 : integratedRightDeflection;
	integratedLeftDeflection = integratedLeftDeflection > 100000 ? 100000 : integratedLeftDeflection;
	integratedRightDeflection = integratedRightDeflection > 100000 ? 100000 : integratedRightDeflection;
	int leftIntegration = integratedLeftDeflection >> 8;
	int rightIntegration = integratedRightDeflection >> 8;
	// 微分項の計算
	int leftDerivative = KD * (leftDeflection - previousLeftDeflection);
	int rightDerivative = KD * (rightDeflection - previousRightDeflection);
	previousLeftDeflection = leftDeflection;
	previousRightDeflection = rightDeflection;
	
	// デューティー比の計算
	// 比例項の適用
	int leftPWMDutyValue = leftProportional;
	int rightPWMDutyValue = rightProportional;
	// 積分項の適用
	leftPWMDutyValue += leftIntegration;
	rightPWMDutyValue += rightIntegration;
	// 微分項の適用
	leftPWMDutyValue += leftDerivative;
	rightPWMDutyValue += rightDerivative;
	// 値の制限
	leftPWMDutyValue = leftPWMDutyValue < 0 ? 0 : leftPWMDutyValue;
	rightPWMDutyValue = rightPWMDutyValue < 0 ? 0 : rightPWMDutyValue;
	printf("tar=%03d spe=%03d P=%03d I=%03d D=%03d dut=%03d\r\n",
			NAMESPACE(leftTarget),
			left,
			leftProportional,
			leftIntegration,
			leftDerivative,
			leftPWMDutyValue);
	NAMESPACE(leftMotorDriver)->setPWMDutyValue(leftPWMDutyValue);
	NAMESPACE(rightMotorDriver)->setPWMDutyValue(rightPWMDutyValue);
	// 割り込み周期は変更しない
	return 0;
}

// substance of interface
static PeriodicInterruptListener NAMESPACE(periodicInterruptListener) = {
	NAMESPACE(onTimerOverflowed),
};

// --------------------------------------------------------------------
// MotionController
// --------------------------------------------------------------------
// field methods
static void NAMESPACE(stop)() {
	NAMESPACE(leftMotorDriver)->setStop();
	NAMESPACE(rightMotorDriver)->setStop();
}

static void NAMESPACE(moveStraight)(int speed) {
	NAMESPACE(leftMotorDriver)->setForward();
	NAMESPACE(rightMotorDriver)->setForward();
	NAMESPACE(leftTarget) = speed;
	NAMESPACE(rightTarget) = speed;
}

static void NAMESPACE(moveCorner)(int speed, int r_inverse) {
	NAMESPACE(leftMotorDriver)->setForward();
	NAMESPACE(rightMotorDriver)->setForward();
	NAMESPACE(leftTarget) = speed;
	NAMESPACE(rightTarget) = speed;
}

static void NAMESPACE(moveDistance)(int speed, unsigned long distance) {
	NAMESPACE(leftMotorDriver)->setForward();
	NAMESPACE(rightMotorDriver)->setForward();
	NAMESPACE(leftTarget) = speed;
	NAMESPACE(rightTarget) = speed;
}

// substance of interface
static MotionController NAMESPACE(motionController) = {
	NAMESPACE(stop),
	NAMESPACE(moveStraight),
	NAMESPACE(moveCorner),
	NAMESPACE(moveDistance),
};

// constructor
MotionController* NAMESPACE(getter)(
		PeriodicInterruptController* periodicInterruptController,
		MotorDriver* leftMotorDriver,
		SpeedCounter* leftSpeedCounter,
		MotorDriver* rightMotorDriver,
		SpeedCounter* rightSpeedCounter) {
	periodicInterruptController->addInterruptListener(&NAMESPACE(periodicInterruptListener));
	periodicInterruptController->enableInterrupt(LOW_PRIORITY);
	
	NAMESPACE(leftMotorDriver) = leftMotorDriver;
	NAMESPACE(leftSpeedCounter) = leftSpeedCounter;

	NAMESPACE(rightMotorDriver) = rightMotorDriver;
	NAMESPACE(rightSpeedCounter) = rightSpeedCounter;

	return &NAMESPACE(motionController);
}


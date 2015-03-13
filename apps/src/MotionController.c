#include "MotionController.h"

#include <stdio.h>

#define MAXIMUM_PWM_DUTY_VALUE 1000
#define KP 4
#define KI 5
#define KD 2	//12

#define NAMESPACE(name) MotionController_##name
#define MotionController_getter getMotionController

// common variables
static MotorDriver* NAMESPACE(leftMotorDriver);
static SpeedCounter* NAMESPACE(leftSpeedCounter);
static MotorDriver* NAMESPACE(rightMotorDriver);
static SpeedCounter* NAMESPACE(rightSpeedCounter);
/**
 * 目標速度（カウント基準）
 * 計算しやすいようにするためintで宣言
 */
static int NAMESPACE(leftTarget);
static int NAMESPACE(rightTarget);
/**
 * 目標移動量が設定されている時に立つフラグ．
 * 目標を達成したらクリアされる．
 */
static uint8_t NAMESPACE(distanceMoveConfigured);
/**
 * 目標移動量
 */
static unsigned long NAMESPACE(leftAimDistance);
static unsigned long NAMESPACE(rightAimDistance);

// --------------------------------------------------------------------
// PeriodicInterruptListener
// --------------------------------------------------------------------
// field methods
static uint16_t NAMESPACE(onTimerOverflowed)() {
	// 8回に1回割り込む
	static uint8_t interruptCount = 0;
	if (interruptCount < 8) {
		interruptCount++;
		return 0;
	} else {
		interruptCount = 0;
	}
	/** 前回の速度偏差（微分項算出に使用） */
	static int previousLeftDeflection;
	static int previousRightDeflection;
	/** 偏差の積分値（積分項算出に使用） */
	static long integratedLeftDeflection = 0;
	static long integratedRightDeflection = 0;
	// スピードの取得
	int left = NAMESPACE(leftSpeedCounter)->getSpeedCount();
	int right = NAMESPACE(rightSpeedCounter)->getSpeedCount();

	// 移動目標量が設定されている場合は加算していく
	if (NAMESPACE(distanceMoveConfigured) == true) {
		static unsigned long leftIntegratedDistance = 0;
		static unsigned long rightIntegratedDistance = 0;
		leftIntegratedDistance += left;
		rightIntegratedDistance += left;
		if (leftIntegratedDistance > NAMESPACE(leftAimDistance) 
			&& rightIntegratedDistance > NAMESPACE(rightAimDistance)) {
			NAMESPACE(leftMotorDriver)->setStop();
			NAMESPACE(rightMotorDriver)->setStop();
			leftIntegratedDistance = 0;
			rightIntegratedDistance = 0;
			NAMESPACE(distanceMoveConfigured) == false;
			return 0;
		}
	}

	// 偏差の計算
	int leftDeflection = NAMESPACE(leftTarget) - left;
	int rightDeflection = NAMESPACE(rightTarget) - right;
	// 比例項の計算
	int leftProportional = KP * leftDeflection;
	int rightProportional = KP * rightDeflection;
	leftProportional = leftProportional > 1000 ? 1000 : leftProportional;
	rightProportional = rightProportional > 1000 ? 1000 : rightProportional;
	// 積分項の計算
	integratedLeftDeflection += leftDeflection;
	integratedRightDeflection += rightDeflection;
	integratedLeftDeflection = integratedLeftDeflection < 0 ? 0 : integratedLeftDeflection;
	integratedRightDeflection = integratedRightDeflection < 0 ? 0 : integratedRightDeflection;
	integratedLeftDeflection = integratedLeftDeflection > 100000 ? 100000 : integratedLeftDeflection;
	integratedRightDeflection = integratedRightDeflection > 100000 ? 100000 : integratedRightDeflection;
	int leftIntegration = (KI * integratedLeftDeflection) >> 6;
	int rightIntegration = (KI * integratedRightDeflection) >> 6;
	// 微分項の計算
	int leftDerivative = KD * (leftDeflection - previousLeftDeflection);
	int rightDerivative = KD * (rightDeflection - previousRightDeflection);
	previousLeftDeflection = leftDeflection;
	previousRightDeflection = rightDeflection;
	
	// デューティー比の計算
	// 初期値代入
	int leftPWMDutyValue = NAMESPACE(leftTarget);
	int rightPWMDutyValue = NAMESPACE(rightTarget);
	// 比例項の適用
	leftPWMDutyValue += leftProportional;
	rightPWMDutyValue += rightProportional;
	// 積分項の適用
	leftPWMDutyValue += leftIntegration;
	rightPWMDutyValue += rightIntegration;
	// 微分項の適用
	leftPWMDutyValue += leftDerivative;
	rightPWMDutyValue += rightDerivative;
	// カウント数からPWMデューティー比への変換式を適用
	// ↓元の式
	//leftPWMDutyValue = ((unsigned long)leftPWMDutyValue * 305) >> 6;
	//rightPWMDutyValue = ((unsigned long)rightPWMDutyValue * 305) >> 6;
	leftPWMDutyValue = ((unsigned long)leftPWMDutyValue * 450) >> 6;
	rightPWMDutyValue = ((unsigned long)rightPWMDutyValue * 450) >> 6;
	// 値の制限
	leftPWMDutyValue = leftPWMDutyValue < 0 ? 0 : leftPWMDutyValue;
	rightPWMDutyValue = rightPWMDutyValue < 0 ? 0 : rightPWMDutyValue;
	leftPWMDutyValue = leftPWMDutyValue > 1000 ? 1000 : leftPWMDutyValue;
	rightPWMDutyValue = rightPWMDutyValue > 1000 ? 1000 : rightPWMDutyValue;
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
	if (speed > 0) {
		NAMESPACE(leftMotorDriver)->setForward();
		NAMESPACE(rightMotorDriver)->setForward();
		NAMESPACE(leftTarget) = speed;
		NAMESPACE(rightTarget) = speed;
	} else {
		NAMESPACE(leftMotorDriver)->setBackward();
		NAMESPACE(rightMotorDriver)->setBackward();
		NAMESPACE(leftTarget) = -speed;
		NAMESPACE(rightTarget) = -speed;
	}
}

static void NAMESPACE(moveCorner)(int speed, int r_inverse) {
	long leftTarget;
	long rightTarget;
	if (speed > 0) {
		leftTarget = (speed * (1024 - 9 * (long)r_inverse)) >> 10;
		rightTarget = (speed * (1024 + 9 * (long)r_inverse)) >> 10;
	} else {
		leftTarget = (-speed * (1024 - 9 * (long)r_inverse)) >> 10;
		rightTarget = (-speed * (1024 + 9 * (long)r_inverse)) >> 10;
	}
	if (leftTarget == 0) {
		NAMESPACE(leftMotorDriver)->setStop();
	} else if (leftTarget > 0) {
		NAMESPACE(leftMotorDriver)->setForward();
	} else {
		NAMESPACE(leftMotorDriver)->setBackward();
	}
	if (rightTarget == 0) {
		NAMESPACE(rightMotorDriver)->setStop();
	} else if (rightTarget > 0) {
		NAMESPACE(rightMotorDriver)->setForward();
	} else {
		NAMESPACE(rightMotorDriver)->setBackward();
	}
	leftTarget = leftTarget > 200 ? 200 : leftTarget;
	rightTarget = rightTarget > 200 ? 200 : rightTarget;
	leftTarget = leftTarget < 0 ? 0 : leftTarget;
	rightTarget = rightTarget < 0 ? 0 : rightTarget;
	NAMESPACE(leftTarget) = leftTarget;
	NAMESPACE(rightTarget) = rightTarget;
}

static void NAMESPACE(moveDistance)(int speed, unsigned long distance) {
	if (speed > 0) {
		NAMESPACE(leftMotorDriver)->setForward();
		NAMESPACE(rightMotorDriver)->setForward();
		NAMESPACE(leftTarget) = speed;
		NAMESPACE(rightTarget) = speed;
	} else {
		NAMESPACE(leftMotorDriver)->setBackward();
		NAMESPACE(rightMotorDriver)->setBackward();
		NAMESPACE(leftTarget) = -speed;
		NAMESPACE(rightTarget) = -speed;
	}
	NAMESPACE(leftAimDistance) = distance;
	NAMESPACE(rightAimDistance) = distance;
	NAMESPACE(distanceMoveConfigured) = true;
	while (NAMESPACE(distanceMoveConfigured) == true) {
		// do nothing
	}
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


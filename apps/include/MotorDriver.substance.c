#ifdef USING_MOTOR_DRIVER_SUBSTANCE

// common field variables
static PeriodicInterruptController* NAMESPACE(periodicInterruptController);
static CompareMatchInterruptController* NAMESPACE(compareMatchInterruptController);
static GPIOPort* NAMESPACE(gpioPort);
static uint8_t NAMESPACE(usePinPattern);
static uint8_t NAMESPACE(freePattern);
static uint8_t NAMESPACE(forwardPattern);
static uint8_t NAMESPACE(backwardPattern);
static uint8_t NAMESPACE(stopPattern);
static uint8_t NAMESPACE(positivePinPatten);
static uint8_t NAMESPACE(negativePinPattern);

// --------------------------------------------------------------------
// PeriodicInterruptListener
// --------------------------------------------------------------------
// field methods
static uint16_t NAMESPACE(onTimerOverflowed)() {
	// do nothing
	return 0;
}

// substance of interface
static PeriodicInterruptListener NAMESPACE(periodicInterruptListener) = {
	NAMESPACE(onTimerOverflowed),
};

// --------------------------------------------------------------------
// CompareMatchInterruptListener
// --------------------------------------------------------------------
// field methods
static uint16_t NAMESPACE(onCompareMatched)() {
	// do nothing
	return 0;
}

// substance of interface
static CompareMatchInterruptListener NAMESPACE(compareMatchInterruptListener) = {
	NAMESPACE(onCompareMatched),
};

// --------------------------------------------------------------------
// Motor Driver
// --------------------------------------------------------------------

// field methods
/*
 * set~ メソッドについて．
 * positiveパターン（周期割り込み時に適用）と
 * negativeパターン（コンペアマッチ割り込み時に適用）
 * の2つを設定する．
 * それぞれ1byteなので割り込みが起こっても中途半端な値で適用されることはない．
 */
static void NAMESPACE(setFree)() {
	NAMESPACE(positivePinPatten) = NAMESPACE(freePattern);
	NAMESPACE(negativePinPattern) = NAMESPACE(freePattern);
}

static void NAMESPACE(setForward)() {
	NAMESPACE(positivePinPatten) = NAMESPACE(forwardPattern);
	NAMESPACE(negativePinPattern) = NAMESPACE(freePattern);
}

static void NAMESPACE(setBackward)() {
	NAMESPACE(positivePinPatten) = NAMESPACE(backwardPattern);
	NAMESPACE(negativePinPattern) = NAMESPACE(freePattern);
}

static void NAMESPACE(setStop)() {
	NAMESPACE(positivePinPatten) = NAMESPACE(stopPattern);
	NAMESPACE(negativePinPattern) = NAMESPACE(stopPattern);
}

static void NAMESPACE(setPWMDutyValue)(uint16_t dutyValue) {
	// dutyValueは0~1023
	// setCompareMatchCountは0~65535
	NAMESPACE(compareMatchInterruptController)->setCompareMatchCount(dutyValue << 6);
}

// substance of interface
MotorDriver NAMESPACE(motorDriver) = {
	NAMESPACE(setFree),
	NAMESPACE(setForward),
	NAMESPACE(setBackward),
	NAMESPACE(setStop),
	NAMESPACE(setPWMDutyValue),
};

// constructor
MotorDriver* NAMESPACE(getter)(
		PeriodicInterruptController* pic,
		CompareMatchInterruptController* cmic,
		GPIOPort* port,
		uint8_t usePinPattern,
		uint8_t freePattern,
		uint8_t forwardPattern,
		uint8_t backwardPattern,
		uint8_t stopPattern) {
	// add interrpt listener
	pic->addInterruptListener(&NAMESPACE(periodicInterruptListener));
	cmic->addCompareMatchInterruptListener(&NAMESPACE(compareMatchInterruptListener));

	// ※割り込みの有効化は外部で行うこと．

	// substitute arguments for fields
	NAMESPACE(periodicInterruptController) = pic;
	NAMESPACE(compareMatchInterruptController) = cmic;
	NAMESPACE(gpioPort) = port;
	NAMESPACE(usePinPattern) = usePinPattern;
	NAMESPACE(freePattern) = freePattern;
	NAMESPACE(forwardPattern) = forwardPattern;
	NAMESPACE(backwardPattern) = backwardPattern;
	NAMESPACE(stopPattern) = stopPattern;

	// 最初はfreeに設定
	NAMESPACE(setFree)();

	// return substance of interface
	return &NAMESPACE(motorDriver);
}

#undef NAMESPACE

#endif

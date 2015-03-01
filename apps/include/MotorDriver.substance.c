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
/**
 * 周期割り込み時にIOに適用される値．
 * set~メソッドで変更される．
 */
static uint8_t NAMESPACE(positivePinPatten);
/**
 * コンペアマッチ割り込み時にIOに適用される値．
 * set~メソッドで変更される．
 */
static uint8_t NAMESPACE(negativePinPattern);
/**
 * コンペアマッチ割り込みの比較対象の値．
 * コンペアマッチ割り込み時に適用される．
 * setPWMDutyValueで0~65535の値に設定される．
 */
static uint16_t NAMESPACE(compareMatchCount)[2];
/**
 * compareMatchCountを書き換えるときに，割り込みが起こると動作不良の原因となる．
 * したがってcompareMatchCountをサイズ2の配列にして，
 * 信用できる値が入っている方のインデックスをこの変数で示す．
 * この変数は0か1の値しか取らないようにする必要がある．
 */
static uint8_t NAMESPACE(compareMatchCountIndex);

// --------------------------------------------------------------------
// PeriodicInterruptListener
// --------------------------------------------------------------------
// field methods
static uint16_t NAMESPACE(onTimerOverflowed)() {
	// ピンの出力の変更
	NAMESPACE(gpioPort)->setValue(
			NAMESPACE(usePinPattern),
			NAMESPACE(positivePinPatten));
	// 周期割り込みの値は固定
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
	// ピンの出力の変更
	NAMESPACE(gpioPort)->setValue(
			NAMESPACE(usePinPattern),
			NAMESPACE(negativePinPattern));
	// 次回コンペアマッチ割り込み時のカウントを設定
	return NAMESPACE(compareMatchCount)[NAMESPACE(compareMatchCountIndex)];
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
	uint16_t count;

	// dutyValueは0~1023
	// compareMatchCountは0~65535
	count = (dutyValue << 6);
	if (NAMESPACE(compareMatchCountIndex) == 0) {
		NAMESPACE(compareMatchCount)[1] = count;
		NAMESPACE(compareMatchCountIndex) = 1;
	} else {
		NAMESPACE(compareMatchCount)[0] = count;
		NAMESPACE(compareMatchCountIndex) = 0;
	}
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
	// add interrpt listener and enable interrupt
	pic->addInterruptListener(&NAMESPACE(periodicInterruptListener));
	pic->setPeriodCount(0xFFFF);
	pic->enableInterrupt(HIGH_PRIORITY);
	cmic->addCompareMatchInterruptListener(&NAMESPACE(compareMatchInterruptListener));
	cmic->enableCompareMatchInterrupt(HIGH_PRIORITY);

	// substitute arguments for fields
	NAMESPACE(periodicInterruptController) = pic;
	NAMESPACE(compareMatchInterruptController) = cmic;
	NAMESPACE(gpioPort) = port;
	NAMESPACE(usePinPattern) = usePinPattern;
	NAMESPACE(freePattern) = freePattern;
	NAMESPACE(forwardPattern) = forwardPattern;
	NAMESPACE(backwardPattern) = backwardPattern;
	NAMESPACE(stopPattern) = stopPattern;

	// initilize fields
	NAMESPACE(compareMatchCountIndex) = 0;
	NAMESPACE(compareMatchCount)[0] = 0;
	NAMESPACE(compareMatchCount)[1] = 0;

	// 最初はfreeに設定
	NAMESPACE(setFree)();

	// return substance of interface
	return &NAMESPACE(motorDriver);
}

#undef NAMESPACE

#endif

#ifdef USING_MOTOR_DRIVER_SUBSTANCE

// common field variables
static PeriodicInterruptController* NAMESPACE(periodicInterruptController);
static CompareMatchInterruptController* NAMESPACE(compareMatchInterruptController);
static GPIOPort* NAMESPACE(gpioPort);

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
static void NAMESPACE(setFree)() {
	// do nothing
}

static void NAMESPACE(setForward)() {
	// do nothing
}

static void NAMESPACE(setBackward)() {
	// do nothing
}

static void NAMESPACE(setStop)() {
	// do nothing
}

static void NAMESPACE(setPWMDutyValue)(uint16_t dutyValue) {
	// do nothing
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
		uint8_t freePattern,
		uint8_t forwardPattern,
		uint8_t backwardPattern,
		uint8_t stopPattern) {
	pic->addInterruptListener(&NAMESPACE(periodicInterruptListener));
	cmic->addCompareMatchInterruptListener(&NAMESPACE(compareMatchInterruptListener));
	return &NAMESPACE(motorDriver);
}

#undef NAMESPACE

#endif

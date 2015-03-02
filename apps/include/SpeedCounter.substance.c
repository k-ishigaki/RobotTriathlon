#ifdef USING_SPEED_COUNTER_SUBSTANCE

// common variables
uint8_t NAMESPACE(speedCount) = 0;
uint8_t NAMESPACE(counter) = 0;

// --------------------------------------------------------------------
// ComparatorChangeListener
// --------------------------------------------------------------------
// field methods
void NAMESPACE(onComparatorOutputChanged)(bool comparatorOutput) {
	NAMESPACE(counter) += comparatorOutput;
}

// substance of interface
static ComparatorChangeListener NAMESPACE(comparatorChangeListener) = {
	NAMESPACE(onComparatorOutputChanged),
};

// --------------------------------------------------------------------
// PeriodicInterruptListener
// --------------------------------------------------------------------
// field methods
uint16_t NAMESPACE(onTimerOverflowed)() {
	NAMESPACE(speedCount) = NAMESPACE(counter);
	NAMESPACE(counter) = 0;
	return 0;
}

// substance of interface
static PeriodicInterruptListener NAMESPACE(periodicInterruptListener) = {
	NAMESPACE(onTimerOverflowed),
};

// --------------------------------------------------------------------
// SpeedCounter
// --------------------------------------------------------------------
// field variables
SpeedCountListener* NAMESPACE(listener);

// field methods
static uint8_t NAMESPACE(getSpeedCount)() {
	return NAMESPACE(speedCount);
}

static void NAMESPACE(addSpeedCountListener)(SpeedCountListener* listener) {
	NAMESPACE(listener) = listener;
}

// substance of interface
static SpeedCounter NAMESPACE(speedCounter) = {
	NAMESPACE(getSpeedCount),
	NAMESPACE(addSpeedCountListener),
};

// constructor
SpeedCounter* NAMESPACE(getter)(
		ComparatorModule* comparator,
		PeriodicInterruptController* periodicInterruptController) {
	comparator->addComparatorChangeListener(&NAMESPACE(comparatorChangeListener));
	comparator->enableComparatorChangeInterrupt(HIGH_PRIORITY);
	periodicInterruptController->addInterruptListener(&NAMESPACE(periodicInterruptListener));
	periodicInterruptController->enableInterrupt(HIGH_PRIORITY);
	periodicInterruptController->setPeriodCount(0xFFFF);
	return &NAMESPACE(speedCounter);
}

#undef NAMESPACE

#endif /* USING_SPEED_COUNTER_SUBSTANCE */

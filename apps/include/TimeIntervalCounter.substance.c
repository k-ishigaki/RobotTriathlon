#ifdef USING_TIME_INTERVAL_COUNTER_SUBSTANCE

// common field variables
bool NAMESPACE(isCaptured) = false;
static InputCaptureController* NAMESPACE(inputCaptureController);
static long NAMESPACE(capturedCount) = 0;

// --------------------------------------------------------------------
// InputCaptureInterruptListener
// --------------------------------------------------------------------
// field methods
static void NAMESPACE(onInputCaptured)(uint16_t capturedCount) {
	NAMESPACE(isCaptured) = true;
	NAMESPACE(inputCaptureController)->disableInputCaptureInterrupt();
	NAMESPACE(capturedCount) = capturedCount;
}

// substance of interface
static InputCaptureInterruptListener NAMESPACE(inputCaptureListener) = {
	NAMESPACE(onInputCaptured),
};

// --------------------------------------------------------------------
// TimeIntervalCounter
// --------------------------------------------------------------------
// field variables
static TimerModule* NAMESPACE(timerModule);
// field methods
static void NAMESPACE(startTimer)() {
	NAMESPACE(timerModule)->stop();
	NAMESPACE(timerModule)->setCount(0);
	NAMESPACE(timerModule)->start();
}

static void NAMESPACE(startCapturing)() {
	NAMESPACE(isCaptured) = false;
	NAMESPACE(inputCaptureController)->enableInputCaptureInterrupt(LOW_PRIORITY);
}

static uint16_t NAMESPACE(getCapturedValue)() {
	if (NAMESPACE(isCaptured) == false) {
		NAMESPACE(capturedCount) = 0;
		return 0;
	}
	return NAMESPACE(capturedCount);
}

// substance of interface
static TimeIntervalCounter NAMESPACE(timeIntervalCounter) = {
	NAMESPACE(startTimer),
	NAMESPACE(startCapturing),
	NAMESPACE(getCapturedValue),
};

// constructor
TimeIntervalCounter* NAMESPACE(getter)(TimerModule* timerModule, DigitalPin* pin, InputCaptureController* inputCaptureController) {
	pin->setDirection(false);
	inputCaptureController->addInputCaptureInterruptListener(&NAMESPACE(inputCaptureListener));
	inputCaptureController->enableInputCaptureInterrupt(LOW_PRIORITY);
	NAMESPACE(timerModule) = timerModule;
	NAMESPACE(inputCaptureController) = inputCaptureController;
	return &NAMESPACE(timeIntervalCounter);
}

#undef NAMESPACE

#endif /* TIME_INTERVAL_COUNTER_H */

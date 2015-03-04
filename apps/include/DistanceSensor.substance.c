#ifdef USING_DISTANCE_SENSOR_SUBSTANCE

// common fields
PWMOutputter* NAMESPACE(pwmOutputter);
TimeIntervalCounter* NAMESPACE(timeIntervalCounter);
uint16_t NAMESPACE(distanceCount);

// --------------------------------------------------------------------
// PeriodicCalledTask（パルス送信+タイマスタートタスク）
// --------------------------------------------------------------------
// field methods
static bool NAMESPACE(onTask1Called)() {
	NAMESPACE(pwmOutputter)->enablePWMOutput();
	NAMESPACE(timeIntervalCounter)->startTimer();
	return false;
}

static PeriodicCalledTask NAMESPACE(task1) = {
	NAMESPACE(onTask1Called),
};

// --------------------------------------------------------------------
// PeriodicCalledTask（パルス無効+待ちタスク）
// --------------------------------------------------------------------
// field methods
static bool NAMESPACE(onTask2Called)() {
	static uint8_t interruptCount = 0;
	if (interruptCount == 0) {
		interruptCount++;
		NAMESPACE(pwmOutputter)->disablePWMOutput();
		return true;
	} else if (interruptCount < 10){
		interruptCount++;
		return true;
	}
	interruptCount = 0;
	return false;
}

static PeriodicCalledTask NAMESPACE(task2) = {
	NAMESPACE(onTask2Called),
};

// --------------------------------------------------------------------
// PeriodicCalledTask（インプットキャプチャ有効+待ちタスク）
// --------------------------------------------------------------------
// field methods
static bool NAMESPACE(onTask3Called)() {
	static uint8_t interruptCount = 0;
	if (interruptCount == 0) {
		interruptCount++;
		NAMESPACE(timeIntervalCounter)->startCapturing();
		return true;
	} else if (interruptCount < 10) {
		interruptCount++;
		return true;
	}
	interruptCount = 0;
	return false;
}

static PeriodicCalledTask NAMESPACE(task3) = {
	NAMESPACE(onTask3Called),
};

// --------------------------------------------------------------------
// PeriodicCalledTask（結果取得タスク）
// --------------------------------------------------------------------
// field methods
static bool NAMESPACE(onTask4Called)() {
	NAMESPACE(distanceCount) = NAMESPACE(timeIntervalCounter)->getCapturedValue();
	return false;
}

static PeriodicCalledTask NAMESPACE(task4) = {
	NAMESPACE(onTask4Called),
};

// --------------------------------------------------------------------
// DistanceSensor
// --------------------------------------------------------------------
// field methods
static uint16_t NAMESPACE(getDistaneCount)() {
	return NAMESPACE(distanceCount);
}

// substance of interface
static DistanceSensor NAMESPACE(distanceSensor) = {
	NAMESPACE(getDistaneCount),
};

// constructor
DistanceSensor* NAMESPACE(getter)(
		PWMOutputter* pwmOutputter,
		TimeIntervalCounter* timeIntervalCounter,
		TaskManager* taskManager) {
	pwmOutputter->disablePWMOutput();
	NAMESPACE(pwmOutputter) = pwmOutputter;
	NAMESPACE(timeIntervalCounter) = timeIntervalCounter;
	return &NAMESPACE(distanceSensor);
}

#undef NAMESPACE

#endif /* USING_DISTANCE_SENSOR_SUBSTANCE */

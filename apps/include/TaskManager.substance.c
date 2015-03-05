#ifdef USING_TASK_MANAGER_SUBSTANCE

// common field variables
PeriodicCalledTask* NAMESPACE(tasks)[10] = {0};
uint8_t NAMESPACE(numberOfTasks) = 0;
uint8_t NAMESPACE(indexOfTaskInProgress) = 0;
bool NAMESPACE(isRegistered) = false;

// --------------------------------------------------------------------
// PeriodicInterruptListener
// --------------------------------------------------------------------
// field methods
uint16_t NAMESPACE(onTimerOverflowed)() {
	// タスクの数が0の時は何も呼び出さない
	if (NAMESPACE(numberOfTasks) == 0) {
		return 0;
	}
	bool continues = NAMESPACE(tasks)[NAMESPACE(indexOfTaskInProgress)]->onTaskCalled();
	if (continues == false) {
		NAMESPACE(indexOfTaskInProgress)++;
		if (NAMESPACE(indexOfTaskInProgress) >= NAMESPACE(numberOfTasks)) {
			// 最後のタスクが終わったら最初のタスクを呼び出す
			NAMESPACE(indexOfTaskInProgress) = 0;
		}
	}
	return 0;
}

// substance of interface
PeriodicInterruptListener NAMESPACE(periodicInterruptListener) = {
	NAMESPACE(onTimerOverflowed),
};

// --------------------------------------------------------------------
// TaskManager
// --------------------------------------------------------------------
// field variables
PeriodicInterruptController* NAMESPACE(periodicInterruptController);

// field methods
void NAMESPACE(addPeriodicCalledTack)(PeriodicCalledTask* task) {
	NAMESPACE(tasks)[NAMESPACE(numberOfTasks)] = task;
	NAMESPACE(numberOfTasks)++;
}

void NAMESPACE(enableTaskInterrupt)() {
	NAMESPACE(periodicInterruptController)->enableInterrupt(LOW_PRIORITY);
}

void NAMESPACE(disableTaskInterrupt)() {
	NAMESPACE(periodicInterruptController)->disableInterrupt();
}

// substance of interface
TaskManager NAMESPACE(taskManager) = {
	NAMESPACE(addPeriodicCalledTack),
	NAMESPACE(enableTaskInterrupt),
	NAMESPACE(disableTaskInterrupt),
};

// constructor
TaskManager* NAMESPACE(getter)(PeriodicInterruptController* periodicInterruptController) {
	if (NAMESPACE(isRegistered) == false) {
		NAMESPACE(isRegistered) = true;
		periodicInterruptController->addInterruptListener(&NAMESPACE(periodicInterruptListener));
	}
	NAMESPACE(periodicInterruptController) = periodicInterruptController;
	return &NAMESPACE(taskManager);
}

#undef NAMESPACE

#endif /* USING_TASK_MANAGER_SUBSTANCE */

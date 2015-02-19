#ifdef USING_TIMER_MODULE_SUBSTANCE

#include <xc.h>

// --------------------------------------------------------------------
// TimerModule_InterruptController
// --------------------------------------------------------------------
TimerModule_InterruptListener* NAMESPACE(listener);

static void NAMESPACE(enableInterrupt)() {
	// 割り込みを有効にする前にTMRxL, TMRxH, TMRxIFはクリアしなければならない
	NAMESPACE(TMRxL).TMRx(L) = 0;
	NAMESPACE(TMRxH).TMRx(H) = 0;
	NAMESPACE(PIRx).TMRx(IF) = 0;
	NAMESPACE(PIEx).TMRx(IE) = 1;
}

static void NAMESPACE(disableInterrupt)() {
	NAMESPACE(PIEx).TMRx(IE) = 0;
	NAMESPACE(PIRx).TMRx(IF) = 0;
}

static void NAMESPACE(addInterruptListener)(TimerModule_InterruptListener* listener) {
	NAMESPACE(listener) = listener;
}

static void NAMESPACE(setInterruptPriority)(int priority) {
	switch ((Hardware_InterruptPriority)priority) {
		case LOW_PRIORITY:
			NAMESPACE(IPRx).TMRx(IP) = 0;
			break;
		case HIGH_PRIORITY:
			NAMESPACE(IPRx).TMRx(IP) = 1;
			break;
	}
}

static TimerModule_InterruptController NAMESPACE(interruptController) = {
	NAMESPACE(enableInterrupt),
	NAMESPACE(disableInterrupt),
	NAMESPACE(setInterruptPriority),
	NAMESPACE(addInterruptListener),
};

static TimerModule_InterruptController* NAMESPACE(getInterruptController)() {
	return &NAMESPACE(interruptController);
}

// --------------------------------------------------------------------
// TimerModule_8bitTimer
// --------------------------------------------------------------------
#ifdef IS_8BIT_TIMER 
static uint8_t NAMESPACE(getCount)() {
	// TODO write code here
}

static void NAMESPACE(setCount)(uint8_t count) {
	// TODO write code here
}

static void NAMESPACE(setPrescalerValue)(uint16_t value) {
	// TODO write code here
}

static void NAMESPACE(setPostscalerValue)(uint16_t divition) {
	if (divition >= 0 && division <= 16) {
		NAMESPACE(TxCON).T2OUTPS = division;
	}
}

static void NAMESPACE(setPeriodCount)(uint8_t count) {
	// TODO write code here
}

static TimerModule_8bitTimer NAMESPACE(8bitTimer) = {
	NAMESPACE(getCount),
	NAMESPACE(setCount),
	NAMESPACE(setPrescalerValue),
	NAMESPACE(setPostscalerValue),
	NAMESPACE(setPeriodCount),
}

static TimerModule_8bitTimer* NAMESPACE(get8bitTimer)() {
	return &NAMESPACE(8bitTimer);
}
# endif

// --------------------------------------------------------------------
// TimerModule_16bitTimer
// --------------------------------------------------------------------
#ifdef IS_16BIT_TIMER
static uint16_t NAMESPACE(getCount)() {
	NAMESPACE(TxCON).Tx(RD16) = 1;
	uint8_t tmrl = NAMESPACE(TMRxL).TMRx(L);
	uint8_t tmrh = NAMESPACE(TMRxH).TMRx(H);
	return tmrl + ((uint16_t)tmrh << 8);
}

static void NAMESPACE(setCount)(uint16_t count) {
	NAMESPACE(TxCON).Tx(RD16) = 1;
	NAMESPACE(TMRxL).TMRx(L) = count;
	NAMESPACE(TMRxH).TMRx(H) = count << 8;
}

static void NAMESPACE(setPrescalerValue)(uint8_t division) {
	switch (division) {
		case 1:
			NAMESPACE(TxCON).Tx(CKPS) = 0b00;
			break;
		case 2:
			NAMESPACE(TxCON).Tx(CKPS) = 0b01;
			break;
		case 4:
			NAMESPACE(TxCON).Tx(CKPS) = 0b10;
			break;
		case 8:
			NAMESPACE(TxCON).Tx(CKPS) = 0b11;
			break;
	}
}

static TimerModule_16bitTimer NAMESPACE(16bitTimer) = {
	NAMESPACE(getCount),
	NAMESPACE(setCount),
	NAMESPACE(setPrescalerValue),
};

static TimerModule_16bitTimer* NAMESPACE(get16bitTimer)() {
	return &NAMESPACE(16bitTimer);
}
#endif

// --------------------------------------------------------------------
// TimerModule
// --------------------------------------------------------------------
static void NAMESPACE(enable)() {
	NAMESPACE(TxCON).TMRx(ON) = 1;
}

static void NAMESPACE(disable)() {
	NAMESPACE(TxCON).TMRx(ON) = 0;
}

static void NAMESPACE(selectClockSource)(int source) {
#ifdef IS_16BIT_TIMER
	switch ((TimerModule_clockSource)source) {
		case CRYSTAL_OSCILLATOR:
			NAMESPACE(TxCON).Tx(SOSCEN) = 1;
			NAMESPACE(TxCON).TMRx(CS) = 0b10;
			break;
		case EXTERNAL_CLOCK:
			NAMESPACE(TxCON).Tx(SOSCEN) = 0;
			NAMESPACE(TxCON).TMRx(CS) = 0b10;
			break;
		case SYSTEM_CLOCK:
			NAMESPACE(TxCON).TMRx(CS) = 0b01;
			break;
		case INSTRUCTION_CLOCK:
			NAMESPACE(TxCON).TMRx(CS) = 0b00;
			break;
	}
#endif
}

static TimerModule NAMESPACE(timerModule) = {
	NAMESPACE(enable),
	NAMESPACE(disable),
	NAMESPACE(selectClockSource),
	NAMESPACE(getInterruptController),
#ifdef IS_8BIT_TIMER
	NAMESPACE(get8bitTimer),
	NULL,
#elif defined IS_16BIT_TIMER
	NULL,
	NAMESPACE(get16bitTimer),
#endif
};

TimerModule* NAMESPACE(getter)() {
	return &NAMESPACE(timerModule);
}

void NAMESPACE(handleInterrupt)() {
	if (NAMESPACE(PIEx).TMRx(IE) == 1 && NAMESPACE(PIRx).TMRx(IF) == 1) {
		// フラグは手動でクリアする必要がある
		NAMESPACE(PIRx).TMRx(IF) = 0;
		// タイマの値を取得する
		NAMESPACE(listener)->onInterrupt();
	}
}

#undef IS_16BIT_TIMER
#undef IS_8BIT_TIMER
#undef NAMESPACE
#undef TMRx
#undef Tx

#endif /* USING_TIMER_MODULE_SUBSTANCE */

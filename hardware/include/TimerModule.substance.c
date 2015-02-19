#ifdef USING_TIMER_MODULE_SUBSTANCE

#include <xc.h>

TimerModule_InterruptListener* NAMESPACE(listener);

static void NAMESPACE(enable)() {
	NAMESPACE(TxCON).TMRx(ON) = 1;
}

static void NAMESPACE(disable)() {
	NAMESPACE(TxCON).TMRx(ON) = 0;
}

static void NAMESPACE(reset)() {
	NAMESPACE(TxCON).TMRx(ON) = 0;
	NAMESPACE(TxCON).TMRx(ON) = 1;
}

static void NAMESPACE(addInterruptListener)(TimerModule_InterruptListener* listener) {
	NAMESPACE(listener) = listener;
}

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

#ifdef IS_16BIT_TIMER /* 16 bit Timer */
static void NAMESPACE(selectClockSource)(int source) {
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
}

static void NAMESPACE(setPrescalerValue)(uint16_t division) {
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

static void NAMESPACE(setCount)(uint16_t count) {
	NAMESPACE(TxCON).Tx(RD16) = 1;
	NAMESPACE(TMRxL).TMRx(L) = count;
	NAMESPACE(TMRxH).TMRx(H) = count << 8;
}

static uint16_t NAMESPACE(getCount)() {
	NAMESPACE(TxCON).Tx(RD16) = 1;
	uint8_t tmrl = NAMESPACE(TMRxL).TMRx(L);
	uint8_t tmrh = NAMESPACE(TMRxH).TMRx(H);
	return tmrl + ((uint16_t)tmrh << 8);
}

static TimerModule NAMESPACE(timerModule) = {
	NAMESPACE(enable),
	NAMESPACE(disable),
	NAMESPACE(reset),
	NAMESPACE(addInterruptListener),
	NAMESPACE(enableInterrupt),
	NAMESPACE(disableInterrupt),
	NAMESPACE(setInterruptPriority),
	NAMESPACE(selectClockSource),
	NAMESPACE(setPrescalerValue),
	NULL,
	NAMESPACE(setCount),
	NAMESPACE(getCount),
	NULL,
};

#elif IS_8BIT_TIMER /* 8 bit Timer */
static void NAMESPACE(setPostscalerValue)(uint16_t division) {
	if (divition >= 0 && division <= 16) {
		NAMESPACE(TxCON).T2OUTPS = division;
	}
}

#else /* other Timer */

#endif

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

#ifdef USING_TIMER_MODULE_SUBSTANCE

#include <xc.h>

// common variables

// --------------------------------------------------------------------
// PeriodicInterruptController
// --------------------------------------------------------------------
// field variables
PeriodicInterruptListener* NAMESPACE(listener);
unsigned long NAMESPACE(periodCount);

// field methods
static void NAMESPACE(setPeriodCount)(uint16_t periodCount) {
	NAMESPACE(periodCount) = periodCount;
}

static void NAMESPACE(addInterruptListener)(PeriodicInterruptListener* listener) {
	NAMESPACE(listener) = listener;
}

static void NAMESPACE(enableInterrupt)(int priority) {
	switch ((Hardware_InterruptPriority)priority) {
		case LOW_PRIORITY:
			NAMESPACE(IPRx).TMRx(IP) = 0;
			break;
		case HIGH_PRIORITY:
			NAMESPACE(IPRx).TMRx(IP) = 1;
			break;
	}
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

// substance of interface
static PeriodicInterruptController NAMESPACE(periodicInterruptController) = {
	NAMESPACE(setPeriodCount),
	NAMESPACE(addInterruptListener),
	NAMESPACE(enableInterrupt),
	NAMESPACE(disableInterrupt),
};

// constructor
static PeriodicInterruptController* NAMESPACE(getPeriodicInterruptController)() {
	return &NAMESPACE(periodicInterruptController);
}


// --------------------------------------------------------------------
// TimerModule
// --------------------------------------------------------------------
static void NAMESPACE(start)() {
	NAMESPACE(TxCON).TMRx(ON) = 1;
}

static void NAMESPACE(stop)() {
	NAMESPACE(TxCON).TMRx(ON) = 0;
}

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
#endif

static TimerModule NAMESPACE(timerModule) = {
	NAMESPACE(start),
	NAMESPACE(stop),
	NAMESPACE(getCount),
	NAMESPACE(setCount),
	NAMESPACE(getPeriodicInterruptController),
};

#ifdef IS_16BIT_TIMER
TimerModule* NAMESPACE(getter)(SixteenBitTimer_ClockSource clockSource, SixteenBitTimer_Prescaler prescaler) {
	switch (clockSource) {
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
	switch (prescaler) {
		case SIXTEEN_BIT_TIMER_PRISCALER_1_1:
			NAMESPACE(TxCON).Tx(CKPS) = 0b00;
			break;
		case SIXTEEN_BIT_TIMER_PRISCALER_1_2:
			NAMESPACE(TxCON).Tx(CKPS) = 0b01;
			break;
		case SIXTEEN_BIT_TIMER_PRISCALER_1_4:
			NAMESPACE(TxCON).Tx(CKPS) = 0b10;
			break;
		case SIXTEEN_BIT_TIMER_PRISCALER_1_8:
			NAMESPACE(TxCON).Tx(CKPS) = 0b11;
			break;
	}
	return &NAMESPACE(timerModule);
}
#elif defined IS_8BIT_TIMER
TimerModule* NAMESPACE(getter)() {
	return &NAMESPACE(timerModule);
}
#else

#endif

void NAMESPACE(handleInterrupt)() {
	if (NAMESPACE(PIEx).TMRx(IE) == 1 && NAMESPACE(PIRx).TMRx(IF) == 1) {
		// フラグは手動でクリアする必要がある
		NAMESPACE(PIRx).TMRx(IF) = 0;
		// 次回割り込みまでのカウント数を取得する
		uint16_t nextPeriodCount = NAMESPACE(listener)->onInterrupt();
		if (nextPeriodCount == 0) {
			nextPeriodCount = NAMESPACE(periodCount);
		} else {
			NAMESPACE(periodCount) = nextPeriodCount;
		}
		// 次回割り込みが指定した値になるようにする
		uint16_t nowCount = NAMESPACE(getCount)();
		// count = nowCount + (MAXIMUM_COUNT - nextPeriodCount)
#ifdef IS_16BIT_TIMER
		NAMESPACE(setCount)(nowCount + (65535 - nextPeriodCount));
#elif defined IS_8BIT_TIMER
		NAMESPACE(setCount)(nowCount + (255 - nextPeriodCount));
#endif
	}
}

#undef IS_16BIT_TIMER
#undef IS_8BIT_TIMER
#undef NAMESPACE
#undef TMRx
#undef Tx

#endif /* USING_TIMER_MODULE_SUBSTANCE */

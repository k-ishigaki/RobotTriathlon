#ifdef USING_TIMER_MODULE_SUBSTANCE

#include <xc.h>

// common variables

// --------------------------------------------------------------------
// PeriodicInterruptController
// --------------------------------------------------------------------
// field variables
PeriodicInterruptListener* NAMESPACE(listener)[2];
int8_t NAMESPACE(numOfListener) = 0;
#ifdef IS_16BIT_TIMER
uint16_t NAMESPACE(periodCount) = 0xFFFF;
#endif

// field methods
static void NAMESPACE(setPeriodCount)(uint16_t periodCount) {
#ifdef IS_16BIT_TIMER
	NAMESPACE(periodCount) = periodCount;
#elif defined IS_8BIT_TIMER
	NAMESPACE(PRx) = periodCount;
#endif
}

static void NAMESPACE(addInterruptListener)(PeriodicInterruptListener* listener) {
	NAMESPACE(listener)[NAMESPACE(numOfListener)] = listener;
	NAMESPACE(numOfListener)++;
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
#ifdef IS_16BIT_TIMER
	// 割り込みを有効にする前にTMRxL, TMRxH, TMRxIFはクリアしなければならない
	NAMESPACE(TMRxL).TMRx(L) = 0;
	NAMESPACE(TMRxH).TMRx(H) = 0;
#endif
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
#ifdef IS_16BIT_TIMER
	NAMESPACE(periodCount) = 0xFFFF;
#elif defined IS_8BIT_TIMER
	NAMESPACE(PRx) = 0xFF;
#endif
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
	// 読み込み順はL->Hとすること(16bit mode)
	uint8_t tmrl = NAMESPACE(TMRxL).TMRx(L);
	uint8_t tmrh = NAMESPACE(TMRxH).TMRx(H);
	return tmrl + ((uint16_t)tmrh << 8);
}

static void NAMESPACE(setCount)(uint16_t count) {
	// 書き込み順はH->Lとすること(16bit mode)
	TMR1H = count >> 8;
	TMR1L = count;
}
#elif defined IS_8BIT_TIMER
static uint16_t NAMESPACE(getCount)() {
	return NAMESPACE(TMRx);
}

static void NAMESPACE(setCount)(uint16_t count) {
	NAMESPACE(TMRx) = count;
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
	// 16bit read/write mode enable
	NAMESPACE(TxCON).Tx(RD16) = 1;
	// select clock source
	switch (clockSource) {
		case SIXTEEN_BIT_TIMER_CLOCKSOURCE_CRYSTAL_OSCILLATOR:
			NAMESPACE(TxCON).Tx(SOSCEN) = 1;
			NAMESPACE(TxCON).TMRx(CS) = 0b10;
			break;
		case SIXTEEN_BIT_TIMER_CLOCKSOURCE_EXTERNAL_CLOCK:
			NAMESPACE(TxCON).Tx(SOSCEN) = 0;
			NAMESPACE(TxCON).TMRx(CS) = 0b10;
			break;
		case SIXTEEN_BIT_TIMER_CLOCKSOURCE_SYSTEM_CLOCK:
			NAMESPACE(TxCON).TMRx(CS) = 0b01;
			break;
		case SIXTEEN_BIT_TIMER_CLOCKSOURCE_INSTRUCTION_CLOCK:
			NAMESPACE(TxCON).TMRx(CS) = 0b00;
			break;
	}
	// select prescaler value
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
TimerModule* NAMESPACE(getter)(EightBitTimer_Priscaler priscaler, EightBitTimer_Postscaler postscaler) {
	NAMESPACE(TxCON).Tx(CKPS) = priscaler;
	NAMESPACE(TxCON).Tx(OUTPS) = postscaler;
	return &NAMESPACE(timerModule);
}
#else

#endif

void NAMESPACE(handleInterrupt)() {
	if (NAMESPACE(PIEx).TMRx(IE) == 1 && NAMESPACE(PIRx).TMRx(IF) == 1) {
		// 次回割り込みまでのカウント数を取得する
		uint16_t nextPeriodCount;
		// リスナ呼び出し
		for (int8_t index = 0; index < NAMESPACE(numOfListener); index++) {
			nextPeriodCount = NAMESPACE(listener)[index]->onInterrupt();
		}
		// 次回割り込みが指定した値になるようにする
#ifdef IS_16BIT_TIMER
		if (nextPeriodCount == 0) {
			nextPeriodCount = NAMESPACE(periodCount);
		} else {
			NAMESPACE(periodCount) = nextPeriodCount;
		}
		if (nextPeriodCount != 0xFFFF) {
			NAMESPACE(setCount)(nextPeriodCount);
		}
#elif defined IS_8BIT_TIMER
		if (nextPeriodCount == 0) {
			// do nothing
		} else {
			NAMESPACE(setPeriodCount)(nextPeriodCount);
		}
#endif
		// フラグはタイマの値を書き換えたあとにクリアする
		NAMESPACE(PIRx).TMRx(IF) = 0;
	}
}

#undef IS_16BIT_TIMER
#undef IS_8BIT_TIMER
#undef NAMESPACE
#undef TMRx
#undef Tx

#endif /* USING_TIMER_MODULE_SUBSTANCE */

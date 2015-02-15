#ifdef USING_TIMER_MODULE_SUBSTANCE

#include <xc.h>

TimerModuleInterruptListener* NAMESPACE(listener);

static void NAMESPACE(enable)() {
	NAMESPACE(txcon).TMR1ON = 1;
}

static void NAMESPACE(disable)() {
	NAMESPACE(txcon).TMR1ON = 0;
}

static void NAMESPACE(reset)() {
	NAMESPACE(txcon).TMR1ON = 0;
	NAMESPACE(txcon).TMR1ON = 1;
}

static void NAMESPACE(addInterruptListener)(TimerModuleInterruptListener* listener) {
	NAMESPACE(listener) = listener;
}

static void NAMESPACE(enableInterrupt)() {
	NAMESPACE(if) = 0;
	NAMESPACE(ie) = 1;
}

static void NAMESPACE(disableInterrupt)() {
	NAMESPACE(ie) = 0;
	NAMESPACE(if) = 0;
}

#ifdef IS_16BIT_TIMER /* 16 bit Timer */
static void NAMESPACE(selectClockSource)(int source) {
	switch ((TimerModule_clockSource)source) {
		case CRYSTAL_OSCILLATOR:
			NAMESPACE(txcon).T1SOSCEN = 1;
			NAMESPACE(txcon).TMR1CS = 0b10;
			break;
		case EXTERNAL_CLOCK:
			NAMESPACE(txcon).T1SOSCEN = 0;
			NAMESPACE(txcon).TMR1CS = 0b10;
			break;
		case SYSTEM_CLOCK:
			NAMESPACE(txcon).TMR1CS = 0b01;
			break;
		case INSTRUCTION_CLOCK:
			NAMESPACE(txcon).TMR1CS = 0b00;
			break;
	}
}

static void NAMESPACE(setPrescalerValue)(uint16_t division) {
	switch (division) {
		case 1:
			NAMESPACE(txcon).T1CKPS = 0b00;
			break;
		case 2:
			NAMESPACE(txcon).T1CKPS = 0b01;
			break;
		case 4:
			NAMESPACE(txcon).T1CKPS = 0b10;
			break;
		case 8:
			NAMESPACE(txcon).T1CKPS = 0b11;
			break;
	}
}

static void NAMESPACE(setCount)(uint16_t count) {
	NAMESPACE(txcon).T1RD16 = 1;
	NAMESPACE(tmrl) = count;
	NAMESPACE(tmrh) = count << 8;
}

static uint16_t NAMESPACE(getCount)() {
	NAMESPACE(txcon).T1RD16 = 1;
	uint8_t tmrl = NAMESPACE(tmrl);
	uint8_t tmrh = NAMESPACE(tmrh);
	return tmrl + ((uint16_t)tmrh << 8);
}

static TimerModule NAMESPACE(timerModule) = {
	NAMESPACE(enable),
	NAMESPACE(disable),
	NAMESPACE(reset),
	NAMESPACE(addInterruptListener),
	NAMESPACE(enableInterrupt),
	NAMESPACE(disableInterrupt),
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
		NAMESPACE(txcon).T2OUTPS = division;
	}
}

#else /* other Timer */

#endif


#undef IS_16BIT_TIMER
#undef IS_8BIT_TIMER
#endif /* USING_TIMER_MODULE_SUBSTANCE */

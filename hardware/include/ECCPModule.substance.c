#ifdef USING_ECCP_MODULE_SUBSTANCE

#include <xc.h>

// --------------------------------------------------------------------
// CompareMatchInterruptController
// --------------------------------------------------------------------
// field variables
CompareMatchInterruptListener* NAMESPACE(listener);

// field methods
static void NAMESPACE(setCompareMatchCount)(uint16_t count) {
	NAMESPACE(CCPRxH).CCPRx(H) = count >> 8;
	NAMESPACE(CCPRxL).CCPRx(L) = count;
}

static void NAMESPACE(addCompareMatchInterruptListener)(CompareMatchInterruptListener* listener){
	NAMESPACE(listener) = listener;
}

static void NAMESPACE(enableCompareMatchInterrupt)(int priority) {
	switch ((Hardware_InterruptPriority)priority) {
		case LOW_PRIORITY:
			NAMESPACE(IPRx).CCPx(IP) = 0;
			break;
		case HIGH_PRIORITY:
			NAMESPACE(IPRx).CCPx(IP) = 1;
			break;
	}
	NAMESPACE(PIRx).CCPx(IF) = 0;
	NAMESPACE(PIEx).CCPx(IE) = 1;
}

static void NAMESPACE(disableCompareMatchInterrupt)() {
	NAMESPACE(PIEx).CCPx(IE) = 0;
	NAMESPACE(PIRx).CCPx(IF) = 0;
}

// substance of interface
static CompareMatchInterruptController NAMESPACE(compareMatchInterruptController) = {
	NAMESPACE(setCompareMatchCount),
	NAMESPACE(addCompareMatchInterruptListener),
	NAMESPACE(enableCompareMatchInterrupt),
	NAMESPACE(disableCompareMatchInterrupt),
};

// constructor
static CompareMatchInterruptController* NAMESPACE(getCompareMatchInterruptController)() {
	NAMESPACE(CCPxCON).CCPx(M) = 0b1010;
	return &NAMESPACE(compareMatchInterruptController);
}

// --------------------------------------------------------------------
// ECCPModule
// --------------------------------------------------------------------
// substance of interface
static ECCPModule NAMESPACE(eccpModule) = {
	&NAMESPACE(getCompareMatchInterruptController),
};

// constructor
ECCPModule* NAMESPACE(getter)(ECCPModule_TimerSource timerSource) {
	switch (timerSource) {
		case ECCP_MODULE_TIMR_SOURCE_TIMER1_TIMER2:
			NAMESPACE(CCPTMRSx).Cx(TSEL) = 0b00;
			break;
		case ECCP_MODULE_TIMR_SOURCE_TIMER3_TIMER4:
			NAMESPACE(CCPTMRSx).Cx(TSEL) = 0b01;
			break;
		case ECCP_MODULE_TIMR_SOURCE_TIMER5_TIMER6:
			NAMESPACE(CCPTMRSx).Cx(TSEL) = 0b10;
			break;
	}
	return &NAMESPACE(eccpModule);
}

// --------------------------------------------------------------------
// ECCPx_handleInterrupt
// --------------------------------------------------------------------
void NAMESPACE(handleInterrupt)() {
	if (NAMESPACE(PIEx).CCPx(IE) == 1 && NAMESPACE(PIRx).CCPx(IF) == 1) {
		uint16_t compareMatchCount;
		
		NAMESPACE(PIRx).CCPx(IF) = 0;
		compareMatchCount = NAMESPACE(listener)->onCompareMatched();
		if (compareMatchCount == 0) {
			// 0が返っていたら変化しない
			return;
		}
		NAMESPACE(setCompareMatchCount)(compareMatchCount);
	}
}

#undef IS_ECCP
#undef IS_CCP
#undef NAMESPACE
#undef CCPx
#undef Cx
#undef CCPRx

#endif /* USING_ECCP_MODULE_SUBSTANCE */

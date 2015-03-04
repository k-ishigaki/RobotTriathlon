#ifdef USING_ECCP_MODULE_SUBSTANCE

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

// --------------------------------------------------------------------
// CompareMatchInterruptController
// --------------------------------------------------------------------
// field variables
CompareMatchInterruptListener* NAMESPACE(listener);

// field methods
static void NAMESPACE(setCompareMatchCount)(uint16_t count) {
	// カウント更新中に割り込みが起こらないようにする
	bool isInterruptEnable;

	isInterruptEnable = NAMESPACE(PIEx).CCPx(IE);
	NAMESPACE(PIEx).CCPx(IE) = 0;
	NAMESPACE(CCPRxH).CCPRx(H) = count >> 8;
	NAMESPACE(CCPRxL).CCPRx(L) = count;
	NAMESPACE(PIEx).CCPx(IE) = isInterruptEnable;
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
// PWMDriver
// --------------------------------------------------------------------

// field methods
static void NAMESPACE(setPWMDutyCount)(uint16_t dutyCount) {
	NAMESPACE(CCPRxL).CCPRx(L) = dutyCount >> 2;
	NAMESPACE(CCPxCON).DCx(B) = dutyCount & 0b11;
}

// substance of interface
static PWMDriver NAMESPACE(pwmDriver) = {
	NAMESPACE(setPWMDutyCount),
};

// constructor
static PWMDriver* NAMESPACE(getPWMDriver)() {
	NAMESPACE(CCPxCON).CCPx(M) = 0b1100;
	return &NAMESPACE(pwmDriver);
}

// --------------------------------------------------------------------
// EnhancedPWMDriver
// --------------------------------------------------------------------
#ifdef IS_ECCP

// field methods
static void NAMESPACE(setPWMOutputMode)(int mode, int outputMode) {
	switch ((EnhancedPWMDriver_Mode)mode) {
		case ENHANCED_PWM_DRIVER_MODE_SINGLE:
			NAMESPACE(CCPxCON).Px(M1) = 0;
			NAMESPACE(CCPxCON).Px(M0) = 0;
			break;
		case ENHANCED_PWM_DRIVER_MODE_HALF_BRIDGE:
			NAMESPACE(CCPxCON).Px(M1) = 1;
			NAMESPACE(CCPxCON).Px(M0) = 0;
			break;
		case ENHANCED_PWM_DRIVER_MODE_FULL_BRIDGE:
			NAMESPACE(CCPxCON).Px(M1) = 0;
			NAMESPACE(CCPxCON).Px(M0) = 1;
			break;
	}
	switch ((EnhancedPWMDriver_OutputMode)outputMode) {
		case ENHANCED_PWM_DRIVER_OUTPUT_MODE_ACTIVE_HIGH_ACTIVE_HIGH:
			NAMESPACE(CCPxCON).CCPx(M) = 0b1100;
			break;
		case ENHANCED_PWM_DRIVER_OUTPUT_MODE_ACTIVE_HIGH_ACTIVE_LOW:
			NAMESPACE(CCPxCON).CCPx(M) = 0b1101;
			break;
		case ENHANCED_PWM_DRIVER_OUTPUT_MODE_ACTIVE_LOW_ACTIVE_HIGH:
			NAMESPACE(CCPxCON).CCPx(M) = 0b1110;
			break;
		case ENHANCED_PWM_DRIVER_OUTPUT_MODE_ACTIVE_LOW_ACTIVE_LOW:
			NAMESPACE(CCPxCON).CCPx(M) = 0b1111;
			break;
	}
}

// substance of interface
static EnhancedPWMDriver NAMESPACE(enhancedPWMDriver) = {
	NAMESPACE(setPWMDutyCount),
	NAMESPACE(setPWMOutputMode),
};

static EnhancedPWMDriver* NAMESPACE(getEnhancedPWMDriver)() {
	// ECCPも最初はシングルアウトプット
	NAMESPACE(CCPxCON).Px(M1) = 0;
	NAMESPACE(CCPxCON).Px(M0) = 0;
	NAMESPACE(CCPxCON).CCPx(M) = 0b1100;
	return &NAMESPACE(enhancedPWMDriver);
}

#endif
// --------------------------------------------------------------------
// ECCPModule
// --------------------------------------------------------------------
// substance of interface
static ECCPModule NAMESPACE(eccpModule) = {
	NAMESPACE(getCompareMatchInterruptController),
	NAMESPACE(getPWMDriver),
#ifdef IS_ECCP
	NAMESPACE(getEnhancedPWMDriver),
#elif defined IS_CCP
	NULL,
#endif
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
#undef DCx
#undef Px

#endif /* USING_ECCP_MODULE_SUBSTANCE */

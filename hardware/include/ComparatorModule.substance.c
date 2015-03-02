#ifdef USING_COMPARATOR_MODULE_SUBSTANCE

#include <xc.h>

// --------------------------------------------------------------------
// CompareMatchInterruptController
// --------------------------------------------------------------------
// field variables
ComparatorChangeListener* NAMESPACE(listener);

// field methods
static void NAMESPACE(selectComparatorChannel)(int channel) {
	switch ((ComparatorModule_Channel)channel) {
		case COMPARATOR_MODULE_CHANNEL_C12IN0:
			NAMESPACE(CMxCON0).Cx(CH) = 0b00;
			break;
		case COMPARATOR_MODULE_CHANNEL_C12IN1:
			NAMESPACE(CMxCON0).Cx(CH) = 0b01;
			break;
		case COMPARATOR_MODULE_CHANNEL_C12IN2:
			NAMESPACE(CMxCON0).Cx(CH) = 0b10;
			break;
		case COMPARATOR_MODULE_CHANNEL_C12IN3:
			NAMESPACE(CMxCON0).Cx(CH) = 0b11;
			break;
	}
}

static bool NAMESPACE(getComparatorOutput)() {
	return NAMESPACE(CMxCON1).MCx(OUT);
}

static void NAMESPACE(addComparatorChangeListener)(ComparatorChangeListener* listener) {
	NAMESPACE(listener) = listener;
}

static void NAMESPACE(enableComparatorChangeInterrupt)(int priority) {
	switch ((Hardware_InterruptPriority)priority) {
		case LOW_PRIORITY:
			NAMESPACE(IPRx).Cx(IP) = 0;
			break;
		case HIGH_PRIORITY:
			NAMESPACE(IPRx).Cx(IP) = 1;
			break;
	}
	NAMESPACE(PIRx).Cx(IF) = 0;
	NAMESPACE(PIEx).Cx(IE) = 1;
}

static void NAMESPACE(disableComparatorChangeInterrupt)() {
	NAMESPACE(PIEx).Cx(IE) = 0;
	NAMESPACE(PIRx).Cx(IF) = 0;
}

// substance of interface
static ComparatorModule NAMESPACE(comparatorModule) = {
	NAMESPACE(selectComparatorChannel),
	NAMESPACE(getComparatorOutput),
	NAMESPACE(addComparatorChangeListener),
	NAMESPACE(enableComparatorChangeInterrupt),
	NAMESPACE(disableComparatorChangeInterrupt),
};

// constructor
ComparatorModule* NAMESPACE(getter)(
		ComparatorModule_Reference reference,
		ComparatorModule_Hysteresis hysteresis,
		ComparatorModule_SynchronousMode synchronousMode) {
	switch (reference) {
		case COMPARATOR_MODULE_REFERENCE_DAC:
			NAMESPACE(CMxCON1).Cx(RSEL) = 0;
			break;
		case COMPARATOR_MODULE_REFERENCE_FVR_BUF1:
			NAMESPACE(CMxCON1).Cx(RSEL) = 1;
			break;
	}
	switch (hysteresis) {
		case COMPARATOR_MODULE_HYSTERESIS_DISABLE:
			NAMESPACE(CMxCON1).Cx(HYS) = 0;
			break;
		case COMPARATOR_MODULE_HYSTERESIS_ENABLE:
			NAMESPACE(CMxCON1).Cx(HYS) = 1;
			break;
	}
	switch (synchronousMode) {
		case COMPARATOR_MODULE_SYNCHRONOUS_MODE_ASYNCHRONOUS:
			NAMESPACE(CMxCON1).Cx(SYNC) = 0;
			break;
		case COMPARATOR_MODULE_SYNCHRONOUS_MODE_T1CLK:
			NAMESPACE(CMxCON1).Cx(SYNC) = 1;
			break;
	}
	NAMESPACE(CMxCON0).Cx(POL) = 1;
	NAMESPACE(CMxCON0).Cx(R) = 1;
	NAMESPACE(CMxCON0).Cx(ON) = 1;
	return &NAMESPACE(comparatorModule);
}

// --------------------------------------------------------------------
// Comparatorx_handleInterrupt
// --------------------------------------------------------------------
void NAMESPACE(handleInterrupt)() {
	if (NAMESPACE(PIEx).Cx(IE) == 1 && NAMESPACE(PIRx).Cx(IF) == 1) {
		NAMESPACE(PIRx).Cx(IF) = 0;
		NAMESPACE(listener)->onComparatorOutputChanged(NAMESPACE(CMxCON0).Cx(OUT));
	}
}

#undef NAMESPACE
#undef Cx
#undef MCx

#endif /* USING_COMPARATOR_MODULE_SUBSTANCE */

/*
 * GPIOピンの実体のうち、繰り返し用いるコードを記述する
 * 他のファイルからはインクルードされないようにガードする
 */
#ifdef USING_GPIO_PIN_SUBSTANCE
#include <stdbool.h>

// --------------------------------------------------------------------
// DigitalPullupedInputPin
// --------------------------------------------------------------------
#ifdef HAS_WEAK_INTERNAL_PULLUP
static bool NAMESPACE(DigitalInputPin_getValue)(void);

static DigitalPullupedInputPin NAMESPACE(digitalPullupedInputPin) = {
	NAMESPACE(DigitalInputPin_getValue),
};

static DigitalPullupedInputPin* NAMESPACE(getPullupedPin)() {
	NAMESPACE(WPUx).WPUxx = 1;
	return &NAMESPACE(digitalPullupedInputPin);
}
#endif

// --------------------------------------------------------------------
// DigitalInputPin
// --------------------------------------------------------------------
static void NAMESPACE(GPIOPin_setDirection)(bool);

static bool NAMESPACE(DigitalInputPin_getValue)() {
	return NAMESPACE(PORTx).Rxx;
}

static DigitalInputPin NAMESPACE(digitalInputPin) = {
	NAMESPACE(DigitalInputPin_getValue),
#ifdef HAS_WEAK_INTERNAL_PULLUP
	NAMESPACE(getPullupedPin),
#else
	NULL
#endif
};

static DigitalInputPin* NAMESPACE(getDigitalInputPin)() {
#ifdef HAS_ANALOG_INTERFACE
	NAMESPACE(ANSELx).ANSxx = 0;
#endif
	NAMESPACE(GPIOPin_setDirection)(false);
	return &NAMESPACE(digitalInputPin);
}

// --------------------------------------------------------------------
// DigitalOutputPin
// --------------------------------------------------------------------
static bool NAMESPACE(DigitalOutputPin_getValue)() {
	return NAMESPACE(LATx).LATxx;
}

static void NAMESPACE(DigitalPin_setValue)(bool);

static DigitalOutputPin NAMESPACE(digitalOutputPin) = {
	NAMESPACE(DigitalOutputPin_getValue),
	NAMESPACE(DigitalPin_setValue),
};

static DigitalOutputPin* NAMESPACE(getDigitalOutputPin)() {
#ifdef HAS_ANALOG_INTERFACE
	NAMESPACE(ANSELx).ANSxx = 0;
#endif
	NAMESPACE(GPIOPin_setDirection)(true);
	return &NAMESPACE(digitalOutputPin);
}

// --------------------------------------------------------------------
// DigitalPin
// --------------------------------------------------------------------

static bool NAMESPACE(DigitalPin_getValue)() {
	if (NAMESPACE(TRISx).TRISxx == 1) {
		return NAMESPACE(DigitalInputPin_getValue)();
	} else {
		return NAMESPACE(DigitalOutputPin_getValue)();
	}
}

static void NAMESPACE(DigitalPin_setValue)(bool value) {
	NAMESPACE(LATx).LATxx = value;
}

static DigitalPin NAMESPACE(digitalPin) = {
	NAMESPACE(GPIOPin_setDirection),
	NAMESPACE(DigitalPin_getValue),
	NAMESPACE(DigitalPin_setValue),
};

static DigitalPin* NAMESPACE(getDigitalPin)() {
#ifdef HAS_ANALOG_INTERFACE
	NAMESPACE(ANSELx).ANSxx = 0;
#endif
	return &NAMESPACE(digitalPin);
}

// --------------------------------------------------------------------
// DigitalPin
// --------------------------------------------------------------------
#ifdef HAS_ANALOG_INTERFACE
static AnalogPin NAMESPACE(analogPin) = {
	NAMESPACE(GPIOPin_setDirection),
};

static AnalogPin* NAMESPACE(getAnalogPin)() {
#ifdef HAS_ANALOG_INTERFACE
	NAMESPACE(ANSELx).ANSxx = 0;
#endif
	return &NAMESPACE(analogPin);
}
#endif

// --------------------------------------------------------------------
// GPIOPin
// --------------------------------------------------------------------
static void NAMESPACE(GPIOPin_setDirection)(bool direction) {
	NAMESPACE(TRISx).TRISxx = !direction;
}

static GPIOPin NAMESPACE(gpioPin) = {
	NAMESPACE(getDigitalInputPin),
	NAMESPACE(getDigitalOutputPin),
	NAMESPACE(getDigitalPin),
#ifdef HAS_ANALOG_INTERFACE
	NAMESPACE(getAnalogPin),
#else
	NULL,
#endif
};

GPIOPin* NAMESPACE(getter)() {
	return &NAMESPACE(gpioPin);
}

#undef HAS_ANALOG_INTERFACE
#undef HAS_WEAK_INTERNAL_PULLUP
#undef NAMESPACE
#undef xx

#endif /* USING_GPIO_PIN_SUBSTANCE */

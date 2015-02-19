/*
 * GPIOピンの実体のうち、繰り返し用いるコードを記述する
 * 他のファイルからはインクルードされないようにガードする
 */
#ifdef USING_GPIO_PIN_SUBSTANCE

static void NAMESPACE(setDigitalInput)() {
	// input
	NAMESPACE(TRISx).TRISxx = 1;
#ifdef HAS_ANALOG_INTERFACE
	// digital
	NAMESPACE(ANSELx).ANSxx = 0;
#endif /* HAS_ANALOG_INTERFACE */
}

static void NAMESPACE(setDigitalOutput)() {
	// output
	NAMESPACE(TRISx).TRISxx = 0;
#ifdef HAS_ANALOG_INTERFACE
	// digital
	NAMESPACE(ANSELx).ANSxx = 0;
#endif /* HAS_ANALOG_INTERFACE */
}

#ifdef HAS_WEAK_INTERNAL_PULLUP
static void NAMESPACE(enableInternalPullup)() {
	NAMESPACE(WPUx).WPUxx = 1;
}

static void NAMESPACE(disableInternalPullup)() {
	NAMESPACE(WPUx).WPUxx = 0;
}
#endif /* HAS_WEAK_INTERNAL_PULLUP */

static unsigned char NAMESPACE(getValue)() {
	return NAMESPACE(PORTx).Rxx;
}

static void NAMESPACE(setValue)(unsigned char value) {
	NAMESPACE(LATx).LATxx = value;
}

#ifdef HAS_ANALOG_INTERFACE
static void NAMESPACE(setAnalogInput)() {
	// input
	NAMESPACE(TRISx).TRISxx = 1;
	// analog
	NAMESPACE(ANSELx).ANSxx = 1;
}

static void NAMESPACE(setAnalogOutput)() {
	// output
	NAMESPACE(TRISx).TRISxx = 0;
	// analog
	NAMESPACE(ANSELx).ANSxx = 1;
}
#endif /* HAS_ANALOG_INTERFACE */

static DigitalPin NAMESPACE(digitalPin) = {
	NAMESPACE(setDigitalInput),
	NAMESPACE(setDigitalOutput),
#ifdef HAS_WEAK_INTERNAL_PULLUP
	NAMESPACE(enableInternalPullup),
	NAMESPACE(disableInternalPullup),
#else
	NULL,
	NULL,
#endif /* HAS_WEAK_INTERNAL_PULLUP */
	NAMESPACE(getValue),
	NAMESPACE(setValue),
};

#ifdef HAS_ANALOG_INTERFACE
static AnalogPin NAMESPACE(analogPin) = {
	NAMESPACE(setAnalogInput),
	NAMESPACE(setAnalogOutput),
};
#endif /* HAS_ANALOG_INTERFACE */

static DigitalPin* NAMESPACE(getDigitalPin)() {
	return &NAMESPACE(digitalPin);
}

#ifdef HAS_ANALOG_INTERFACE
static AnalogPin* NAMESPACE(getAnalogPin)() {
	return &NAMESPACE(analogPin);
}
#endif /* HAS_ANALOG_INTERFACE */

static GPIOPin NAMESPACE(gpioPin) = {
	NAMESPACE(getDigitalPin),
#ifdef HAS_ANALOG_INTERFACE
	NAMESPACE(getAnalogPin),
#else
	NULL,
#endif /* HAS_ANALOG_INTERFACE */
};

GPIOPin* NAMESPACE(getter)() {
	return &NAMESPACE(gpioPin);
}

#undef HAS_ANALOG_INTERFACE
#undef HAS_WEAK_INTERNAL_PULLUP
#undef NAMESPACE
#undef xx

#endif /* USING_GPIO_PIN_SUBSTANCE */

/*
 * GPIOピンの実体のうち、繰り返し用いるコードを記述する
 * 他のファイルからはインクルードされないようにガードする
 */
#ifdef USING_GPIO_PIN_SUBSTANCE

static void NAMESPACE(setDigitalInput)() {
	// input
	NAMESPACE(TRISx) = 1;
#ifdef HAS_ANALOG_INTERFACE
	// digital
	NAMESPACE(ANSELx) = 0;
#endif /* HAS_ANALOG_INTERFACE */
}

static void NAMESPACE(setDigitalOutput)() {
	// output
	NAMESPACE(TRISx) = 0;
#ifdef HAS_ANALOG_INTERFACE
	// digital
	NAMESPACE(ANSELx) = 0;
#endif /* HAS_ANALOG_INTERFACE */
}

static unsigned char NAMESPACE(getValue)() {
	return NAMESPACE(PORTx);
}

static void NAMESPACE(setValue)(unsigned char value) {
	NAMESPACE(LATx) = value;
}

#ifdef HAS_ANALOG_INTERFACE
static void NAMESPACE(setAnalogInput)() {
	// input
	NAMESPACE(TRISx) = 1;
	// analog
	NAMESPACE(ANSELx) = 1;
}

static void NAMESPACE(setAnalogOutput)() {
	// output
	NAMESPACE(TRISx) = 0;
	// analog
	NAMESPACE(ANSELx) = 1;
}
#endif /* HAS_ANALOG_INTERFACE */

static DigitalPin NAMESPACE(digitalPin) = {
	NAMESPACE(setDigitalInput),
	NAMESPACE(setDigitalOutput),
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

#undef HAS_ANALOG_INTERFACE

#endif /* USING_GPIO_PIN_SUBSTANCE */

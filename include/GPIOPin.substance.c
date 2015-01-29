/*
 * GPIOピンの実体のうち、繰り返し用いるコードを記述する
 * 他のファイルからはインクルードされないようにガードする
 */
#ifdef USING_GPIO_PIN_SUBSTANCE

static void NAMESPACE(setDigitalInput)() {
	// input
	NAMESPACE(tris) = 1;
#ifdef HAS_ANALOG_INTERFACE
	// digital
	NAMESPACE(ansel) = 0;
#endif
}

static void NAMESPACE(setDigitalOutput)() {
	// output
	NAMESPACE(tris) = 0;
#ifdef HAS_ANALOG_INTERFACE
	// digital
	NAMESPACE(ansel) = 0;
#endif
}

static unsigned char NAMESPACE(getValue)() {
	return NAMESPACE(port);
}

static void NAMESPACE(setValue)(unsigned char value) {
	NAMESPACE(lat) = value;
}

#ifdef HAS_ANALOG_INTERFACE
static void NAMESPACE(setAnalogInput)() {
	// input
	NAMESPACE(tris) = 1;
	// analog
	NAMESPACE(ansel) = 1;
}

static void NAMESPACE(setAnalogOutput)() {
	// output
	NAMESPACE(tris) = 0;
	// analog
	NAMESPACE(ansel) = 1;
}
#endif

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
#endif

static DigitalPin* NAMESPACE(getDigitalPin)() {
	return &NAMESPACE(digitalPin);
}

#ifdef HAS_ANALOG_INTERFACE
static AnalogPin* NAMESPACE(getAnalogPin)() {
	return &NAMESPACE(analogPin);
}
#endif

static GPIOPin NAMESPACE(gpioPin) = {
	NAMESPACE(getDigitalPin),
#ifdef HAS_ANALOG_INTERFACE
	NAMESPACE(getAnalogPin),
#else
	NULL,
#endif
};

#undef HAS_ANALOG_INTERFACE

#endif

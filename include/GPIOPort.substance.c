/*
 * GPIOポートの実体生成部
 * GPIOPortモジュールを利用するソースコードによってインクルードされる
 */

// 普通のソースコードからはインクルードできないようにする
#ifdef USING_GPIO_PORT_SUBSTANCE

static void NAMESPACE(setAnalogInput)(unsigned char pattern) {
	NAMESPACE(ansel) |= pattern;
	NAMESPACE(tris) |= pattern;
}

static void NAMESPACE(setAnalogOutput)(unsigned char pattern) {
	NAMESPACE(ansel) |= pattern;
	NAMESPACE(tris) &= ~pattern;
}

static void NAMESPACE(setDigitalInput)(unsigned char pattern) {
	NAMESPACE(ansel) &= ~pattern;
	NAMESPACE(tris) |= pattern;
}

static void NAMESPACE(setDigitalOutput)(unsigned char pattern) {
	NAMESPACE(ansel) &= ~pattern;
	NAMESPACE(tris) &= ~pattern;
}

static unsigned char NAMESPACE(getValue)() {
	return NAMESPACE(port);
}

static void NAMESPACE(setValue)(unsigned char pattern) {
	NAMESPACE(lat) = pattern;
}

static GPIOPort NAMESPACE(gpioPort) = {
	NAMESPACE(setAnalogInput),
	NAMESPACE(setAnalogOutput),
	NAMESPACE(setDigitalInput),
	NAMESPACE(setDigitalOutput),
	NAMESPACE(getValue),
	NAMESPACE(setValue),
};

#endif /* USING_GPIO_PORT_SUBSTANCE */

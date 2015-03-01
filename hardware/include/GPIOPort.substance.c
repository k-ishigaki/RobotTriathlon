/*
 * GPIOポートの実体生成部
 * GPIOPortモジュールを利用するソースコードによってインクルードされる
 */

// 普通のソースコードからはインクルードできないようにする
#ifdef USING_GPIO_PORT_SUBSTANCE

static void NAMESPACE(setAnalogInput)(uint8_t pattern) {
	NAMESPACE(ansel) |= pattern;
	NAMESPACE(tris) |= pattern;
}

static void NAMESPACE(setAnalogOutput)(uint8_t pattern) {
	NAMESPACE(ansel) |= pattern;
	NAMESPACE(tris) &= ~pattern;
}

static void NAMESPACE(setDigitalInput)(uint8_t pattern) {
	NAMESPACE(ansel) &= ~pattern;
	NAMESPACE(tris) |= pattern;
}

static void NAMESPACE(setDigitalOutput)(uint8_t pattern) {
	NAMESPACE(ansel) &= ~pattern;
	NAMESPACE(tris) &= ~pattern;
}

static uint8_t NAMESPACE(getValue)() {
	return NAMESPACE(port);
}

static void NAMESPACE(setValue)(uint8_t pattern, uint8_t value) {
	NAMESPACE(lat) = (NAMESPACE(lat) & (~pattern)) | (value & pattern);
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

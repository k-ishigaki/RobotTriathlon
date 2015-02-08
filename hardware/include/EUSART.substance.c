/*
 * EUSARTモジュールの実体生成部
 * EUSARTモジュールを利用するソースコードによってインクルードされる
 * 関数定義と変数定義が含まれるため、インクルードする場所には気をつける必要がある
 * 普通のソースコードからはインクルードしてはいけない
 */

// 普通のソースコードからはインクルードできないようにする
#ifdef USING_EUSART_SUBSTANCE

static void NAMESPACE(reset)() {
	NAMESPACE(rcsta).SPEN = 0;
	NAMESPACE(rcsta).SPEN = 1;
}

static void NAMESPACE(setBaudRate)(unsigned long baudRate) {
	// errataによるとBRGH=1,BRG16=1を使わないとスタートビットを逃すことがあるらしい
	NAMESPACE(txsta).BRGH = 1;
	NAMESPACE(baudcon).BRG16 = 1;
	// (baud rate) = F_OSC / (4 * (n + 1))
	// n = F_OSC / (4 * (baud rate)) - 1
	uint16_t regValue = OPERATING_FREQUENCY / (4 * (baudRate + 1));
	NAMESPACE(spbrgh) = regValue >> 8;
	NAMESPACE(spbrg) = regValue;
}

static void NAMESPACE(enable)() {
	NAMESPACE(txsta).TXEN = 1;
	NAMESPACE(rcsta).SPEN = 1;
}

static void NAMESPACE(disable)() {
	NAMESPACE(txsta).TXEN = 0;
	NAMESPACE(rcsta).SPEN = 0;
}

static uint8_t NAMESPACE(read)() {
	return NAMESPACE(rcreg);
}

static void NAMESPACE(write)(uint8_t data) {
	while(NAMESPACE(txsta).TRMT == 0) {
		// wait for TSR empty
	}
	NAMESPACE(txreg) = data;
}

static Eusart NAMESPACE(eusart) = {
	NAMESPACE(reset),
	NAMESPACE(setBaudRate),
	NAMESPACE(enable),
	NAMESPACE(disable),
	NAMESPACE(read),
	NAMESPACE(write),
};

#endif /* USING_EUSART_SUBSTANCE */

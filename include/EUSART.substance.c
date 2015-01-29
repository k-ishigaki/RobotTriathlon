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
	NAMESPACE(txsta).BRGH = 0;
	NAMESPACE(baudcon).BRG16 = 1;
	// (baud rate) = F_OSC / (16 * (n + 1))
	// n = F_OSC / (16 * (baud rate)) - 1
	NAMESPACE(spbrg) = OPERATING_FREQUENCY / (16 * baudRate) - 1;
}

static void NAMESPACE(enable)() {
	NAMESPACE(txsta).TXEN = 1;
	NAMESPACE(rcsta).SPEN = 1;
}

static void NAMESPACE(disable)() {
	NAMESPACE(txsta).TXEN = 0;
	NAMESPACE(rcsta).SPEN = 0;
}

static char NAMESPACE(read)() {
	return NAMESPACE(rcreg);
}

static void NAMESPACE(write)(char data) {
	while(NAMESPACE(txsta).TRMT == 1) {
		// wait for TSR empty
	}
	TXREG = data;
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

/*
 * EUSARTモジュールの実体生成部
 * EUSARTモジュールを利用するソースコードによってインクルードされる
 * 関数定義と変数定義が含まれるため、インクルードする場所には気をつける必要がある
 * 普通のソースコードからはインクルードしてはいけない
 */

// 普通のソースコードからはインクルードできないようにする
#ifdef USING_EUSART_SUBSTANCE

EusartInterruptListener* NAMESPACE(listener);

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
	NAMESPACE(rcsta).CREN = 1;
}

static void NAMESPACE(disable)() {
	NAMESPACE(txsta).TXEN = 0;
	NAMESPACE(rcsta).SPEN = 0;
	NAMESPACE(rcsta).CREN = 0;
}

static void NAMESPACE(addInterruptListener)(EusartInterruptListener* listener) {
	NAMESPACE(listener) = listener;
}

static void NAMESPACE(enableRXInterrupt)() {
	NAMESPACE(rcie) = 1;
}

static void NAMESPACE(disableRXInterrupt)() {
	NAMESPACE(rcie) = 0;
}

static void NAMESPACE(enableTXInterrupt)() {
	NAMESPACE(txie) = 1;
}

static void NAMESPACE(disableTXInterrupt)() {
	NAMESPACE(txie) = 0;
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
	NAMESPACE(addInterruptListener),
	NAMESPACE(enableRXInterrupt),
	NAMESPACE(disableRXInterrupt),
	NAMESPACE(enableTXInterrupt),
	NAMESPACE(disableTXInterrupt),
	NAMESPACE(read),
	NAMESPACE(write),
};

void NAMESPACE(handleInterrupt)() {
	if ((NAMESPACE(rcie) == 1) && (NAMESPACE(rcif) == 1)) {
		while (NAMESPACE(rcif) == 1) {
			// 受信バッファがなくなるまで読みだす
			NAMESPACE(listener)->onReceived(NAMESPACE(read)());
		}
	}
	if ((NAMESPACE(txie) == 1) && (NAMESPACE(txif) == 1)) {
		uint8_t nextData = NAMESPACE(listener)->onTransmitted();
		if (nextData == 0) {
			// 0の場合は送信をやめる
			NAMESPACE(txie) = 0;
		} else {
			// 0以外の場合は送信を続ける
			NAMESPACE(write)(nextData);
		}
	}
}

#endif /* USING_EUSART_SUBSTANCE */

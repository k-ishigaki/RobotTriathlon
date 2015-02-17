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
	NAMESPACE(RCSTAx).SPEN = 0;
	NAMESPACE(RCSTAx).SPEN = 1;
}

static void NAMESPACE(setBaudRate)(unsigned long baudRate) {
	// errataによるとBRGH=1,BRG16=1を使わないとスタートビットを逃すことがあるらしい
	NAMESPACE(TXSTAx).BRGH = 1;
	NAMESPACE(BAUDCONx).BRG16 = 1;
	// (baud rate) = F_OSC / (4 * (n + 1))
	// n = F_OSC / (4 * (baud rate)) - 1
	uint16_t regValue = OPERATING_FREQUENCY / (4 * (baudRate + 1));
	NAMESPACE(SPBRGHx).SPx(BRGH) = regValue >> 8;
	NAMESPACE(SPBRGx).SPx(BRG) = regValue;
}

static void NAMESPACE(enable)() {
	NAMESPACE(TXSTAx).TXEN = 1;
	NAMESPACE(RCSTAx).SPEN = 1;
	NAMESPACE(RCSTAx).CREN = 1;
}

static void NAMESPACE(disable)() {
	NAMESPACE(TXSTAx).TXEN = 0;
	NAMESPACE(RCSTAx).SPEN = 0;
	NAMESPACE(RCSTAx).CREN = 0;
}

static void NAMESPACE(addInterruptListener)(EusartInterruptListener* listener) {
	NAMESPACE(listener) = listener;
}

static void NAMESPACE(enableRXInterrupt)() {
	NAMESPACE(PIEx).RCx(IE) = 1;
}

static void NAMESPACE(disableRXInterrupt)() {
	NAMESPACE(PIEx).RCx(IE) = 0;
}

static void NAMESPACE(setRXInterruptPriority)(int priority) {
	switch ((Hardware_InterruptPriority)priority) {
		case LOW_PRIORITY:
			NAMESPACE(IPRx).RCx(IP) = 0;
			break;
		case HIGH_PRIORITY:
			NAMESPACE(IPRx).RCx(IP) = 1;
			break;
	}
}

static void NAMESPACE(enableTXInterrupt)() {
	NAMESPACE(PIEx).TXx(IE) = 1;
}

static void NAMESPACE(disableTXInterrupt)() {
	NAMESPACE(PIEx).TXx(IE) = 0;
}

static void NAMESPACE(setTXInterruptPriority)(int priority) {
	switch ((Hardware_InterruptPriority)priority) {
		case LOW_PRIORITY:
			NAMESPACE(IPRx).TXx(IP) = 0;
			break;
		case HIGH_PRIORITY:
			NAMESPACE(IPRx).TXx(IP) = 1;
			break;
	}
}

static uint8_t NAMESPACE(read)() {
	return NAMESPACE(RCREGx).RCx(REG);
}

static void NAMESPACE(write)(uint8_t data) {
	while(NAMESPACE(TXSTAx).TRMT == 0) {
		// wait for TSR empty
	}
	NAMESPACE(TXREGx).TXx(REG) = data;
}

static Eusart NAMESPACE(eusart) = {
	NAMESPACE(reset),
	NAMESPACE(setBaudRate),
	NAMESPACE(enable),
	NAMESPACE(disable),
	NAMESPACE(addInterruptListener),
	NAMESPACE(enableRXInterrupt),
	NAMESPACE(disableRXInterrupt),
	NAMESPACE(setRXInterruptPriority),
	NAMESPACE(enableTXInterrupt),
	NAMESPACE(disableTXInterrupt),
	NAMESPACE(setTXInterruptPriority),
	NAMESPACE(read),
	NAMESPACE(write),
};

Eusart* NAMESPACE(getter)() {
	return &NAMESPACE(eusart);
}

void NAMESPACE(handleInterrupt)() {
	if ((NAMESPACE(PIEx).RCx(IE) == 1) && (NAMESPACE(PIRx).RCx(IF) == 1)) {
		while (NAMESPACE(PIRx).RCx(IF) == 1) {
			// 受信バッファがなくなるまで読みだす
			NAMESPACE(listener)->onReceived(NAMESPACE(read)());
		}
	}
	if ((NAMESPACE(PIEx).TXx(IE) == 1) && (NAMESPACE(PIRx).TXx(IF) == 1)) {
		uint8_t nextData = NAMESPACE(listener)->onTransmitted();
		if (nextData == 0) {
			// 0の場合は送信をやめる
			NAMESPACE(PIEx).TXx(IE) = 0;
		} else {
			// 0以外の場合は送信を続ける
			NAMESPACE(write)(nextData);
		}
	}
}

#undef RCx
#undef TXx
#undef SPx
#undef NAMESPACE

#endif /* USING_EUSART_SUBSTANCE */

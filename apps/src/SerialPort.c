/**
 * シリアルポート
 * EUSARTモジュールを用いてシリアル通信を行う
 * EUSARTの割り込みとリングバッファを使用
 */
#include "SerialPort.h"
#include "Hardware.h"

#define NAMESPACE(name) SerialPort_##name
#define BUF_SIZE 64
#define BUF_SIZE_LIMIT_MASK 0b00111111

/*
 * リングバッファの仕様について
 * バッファのサイズはBUF_SIZEで表し，BUF_SIZE_LIMIT_MASKをAND演算することで
 * 値の制限ができるようにする（BUF_SIZEは2の階乗＆128以内）．
 * バッファの実体は配列とし，
 * 受信用：receiveBuffer，送信用：transmitBufferとする．
 * 受信・送信バッファに「書き込む」時の配列インデックスを
 * receiveBufferIndex，transmitBufferIndexとし，
 * 読み込むときの配列インデックスを
 * (receiveBufferIndex - availableReadCounter) & BUF_SIZE_LIMIT_MASK，
 * (transmitBufferIndex - stillTransmittingCounter) & BUF_SIZE_LIMIT_MASKと
 * なるように統一している
 */

// EUSARTモジュールへの参照
Eusart* NAMESPACE(uart);
// 受信バッファの実体
uint8_t NAMESPACE(receiveBuffer)[BUF_SIZE];
// 受信バッファへの書き込み位置
uint8_t NAMESPACE(receiveBufferIndex);
// 受信バッファの内，読み出し可能な数
uint8_t NAMESPACE(availableReadCounter);
// 送信バッファの実体
uint8_t NAMESPACE(transmitBuffer)[BUF_SIZE];
// 送信バッファへの書き込み位置
uint8_t NAMESPACE(transmitBufferIndex);
// 送信バッファの内，まだ送信していない数
uint8_t NAMESPACE(stillTransmittingCounter);

static void NAMESPACE(onReceived)(uint8_t data) {
	// 受信データをバッファに格納
	NAMESPACE(receiveBuffer)[NAMESPACE(receiveBufferIndex)] = data;
	// インデックスを1増やす
	NAMESPACE(receiveBufferIndex) = (NAMESPACE(receiveBufferIndex) + 1) & BUF_SIZE_LIMIT_MASK;
	// 読み出し可能数を1増やす
	NAMESPACE(availableReadCounter)++;
}

static uint8_t NAMESPACE(onTransmitted)() {
	// 送信するものがない場合は0を返す
	if (NAMESPACE(stillTransmittingCounter) == 0) {
		return 0;
	}
	// バッファポインタが示すデータを見る
	uint8_t nextData = NAMESPACE(transmitBuffer)[
		(NAMESPACE(transmitBufferIndex) - NAMESPACE(stillTransmittingCounter))
		& BUF_SIZE_LIMIT_MASK];
	// 未送信数を1つ減らす
	NAMESPACE(stillTransmittingCounter)--;
	// 0以外なら送信が続けられ，0なら送信をやめて送信割り込みを無効にする
	return nextData;
}

EusartInterruptListener NAMESPACE(listener) = {
	NAMESPACE(onReceived),
	NAMESPACE(onTransmitted),
};

static uint8_t NAMESPACE(read)() {
	// 読み出すものがない場合は0を返す
	if (NAMESPACE(availableReadCounter == 0)) {
		return 0;
	}
	uint8_t data = NAMESPACE(receiveBuffer)[
		(NAMESPACE(receiveBufferIndex) - NAMESPACE(availableReadCounter))
		& BUF_SIZE_LIMIT_MASK];
	// 読み出し可能数を1減らす
	NAMESPACE(availableReadCounter)--;
	return data;
}

static ByteInputStream NAMESPACE(byteInputStream) = {
	NAMESPACE(read),
};

static void NAMESPACE(write)(uint8_t data) {
	// SerialPortは0を送信できない仕様
	if (data == 0){
		return;
	}
	// バッファを変更している間に割り込みが起こらないようにする
	NAMESPACE(uart)->disableTXInterrupt();
	// 送信データをバッファに格納
	NAMESPACE(transmitBuffer)[NAMESPACE(transmitBufferIndex)] = data;
	// バッファポインタを1増やす
	NAMESPACE(transmitBufferIndex) = (NAMESPACE(transmitBufferIndex) + 1) & BUF_SIZE_LIMIT_MASK;
	// 未送信数を1増やす
	NAMESPACE(stillTransmittingCounter)++;
	// 送信割り込みを有効にする
	NAMESPACE(uart)->enableTXInterrupt();
}

static ByteOutputStream NAMESPACE(byteOutputStream) = {
	NAMESPACE(write),
};

static ByteInputStream* NAMESPACE(getByteInputStream)() {
	return &NAMESPACE(byteInputStream);
}

static ByteOutputStream* NAMESPACE(getByteOutputStream)() {
	return &NAMESPACE(byteOutputStream);
}

static SerialPort NAMESPACE(serialPort) = {
	NAMESPACE(getByteInputStream),
	NAMESPACE(getByteOutputStream),
};

SerialPort* getSerialPort(
		DigitalPin* rxPin,
		DigitalPin* txPin,
		Eusart* uart,
		unsigned long baudRate) {
	NAMESPACE(uart) = uart;
	// rxのピンもデジタル入力にする必要がある
	rxPin->setDigitalInput();
	txPin->setDigitalInput();
	NAMESPACE(uart)->setBaudRate(baudRate);
	NAMESPACE(uart)->enable();
	NAMESPACE(uart)->addInterruptListener(&NAMESPACE(listener));
	NAMESPACE(uart)->enableRXInterrupt();
	// リングバッファの初期化
	NAMESPACE(receiveBufferIndex) = 0;
	NAMESPACE(transmitBufferIndex) = 0;
	NAMESPACE(availableReadCounter) = 0;
	NAMESPACE(stillTransmittingCounter) = 0;
	return &NAMESPACE(serialPort);
}


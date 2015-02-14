/*
 * SerialPortのインターフェース
 */

#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include <stdint.h>
#include "GPIOPin.h"
#include "EUSART.h"

typedef struct {
	/**
	 * ストリームから1byte読み込む
	 * @return 読み込んだデータ，データがない場合は0を返す
	 */
	uint8_t (*read)(void);
} ByteInputStream;

typedef struct {
	/**
	 * ストリームに1byte書き込む
	 * @param data 書き込むデータ，0を書き込んでも送信しない
	 */
	void (*write)(uint8_t data);
} ByteOutputStream;

typedef struct {
	/**
	 * byte input steremを返す
	 * @return ByteInputStreamインターフェース
	 */
	ByteInputStream* (*getByteInputStream)(void);
	/**
	 * byte output streamを返す
	 * @return ByteOutputStreamインターフェース
	 */
	ByteOutputStream* (*getByteOutputStream)(void);
} SerialPort;

/**
 * シリアルポートのインスタンスを取得する
 * @param rxDigitalPin RXのデジタルピン
 * @param txDigitalPin TXのデジタルピン
 * @param uart Eusartのインスタンス
 * @param baudRate ボーレート
 */
SerialPort* getSerialPort(
		DigitalPin* rxPin,
		DigitalPin* txPin,
		Eusart* uart,
		unsigned long baudRate);

#endif /* SERIAL_PORT_H */

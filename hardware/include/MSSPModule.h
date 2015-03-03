/*
 * MSSP Moduleのインターフェース．
 * 今のところI2Cしか対応していない．
 */
#ifndef MSSP_MODULE_H
#define MSSP_MODULE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	/**
	 * I2Cで読み込む
	 * @param スレーブのI2Cアドレス
	 * @param 読み込み先のコマンドアドレス
	 * @param 受信するbyte数
	 * @param 受信するバッファの先頭ポインタ（配列）
	 */
	void (*read)(uint8_t, uint8_t, uint8_t, uint8_t*);
	/**
	 * I2Cで書き込む
	 * @param スレーブのI2Cアドレス
	 * @param 書き込むコマンドアドレス
	 * @param 送信するbyte数
	 * @param 送信するバッファの先頭ポインタ（配列）
	 */
	void (*write)(uint8_t, uint8_t, uint8_t, uint8_t*);
} I2CInterface;

typedef struct {
	/**
	 * I2Cのインターフェースを取得する．
	 */
	I2CInterface* (*getI2CInterface)();
} MSSPModule;

#endif /* MSSP_MODULE_H */

/*
 * PICのEUSARTモジュールを操作するオブジェクト
 * とりあえずは使わない機能（同期通信など）を省いて、基本機能のみ抑える
 */

#ifndef EUSART_H
#define EUSART_H

#include <stdint.h>

// EUSARTのオブジェクト
// EUSART.cで実体を定義
typedef struct {
	/**
	 * 現在の設定のまま、シリアルポートをリセットする
	 * エラーで動作しない場合に呼び出すこと
	 */
	void (*reset)(void);
	/**
	 * ボーレートを設定する
	 * @param baudRate ボーレート、整数で指定
	 */
	void (*setBaudRate)(unsigned long baudRate);
	/**
	 * EUSARTを有効にする
	 */
	void (*enable)(void);
	/**
	 * EUSARTを無効にする
	 */
	void (*disable)(void);
	/**
	 * 1byte受信する
	 * @return 受信データ
	 */
	uint8_t (*read)(void);
	/**
	 * 1byte送信する
	 * @param data 送信するデータ
	 */
	void (*write)(uint8_t data);
} Eusart;

#endif /* EUSART_H */

/*
 * PICのEUSARTモジュールを操作するオブジェクト
 * とりあえずは使わない機能（同期通信など）を省いて、基本機能のみ抑える
 */

#ifndef EUSART_H
#define EUSART_H

#include <stdint.h>

// EUSARTの割り込みリスナ
typedef struct {
	/**
	 * 受信時に呼び出される
	 * @param data 受信したデータ
	 */
	void (*onReceived)(uint8_t data);
	/**
	 * 送信完了時に呼び出される
	 * @return 次に送信するデータ、送信しない場合は0を返すこと
	 */
	uint8_t (*onTransmitted)(void);
} EusartInterruptListener;

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
	 * 割り込みリスナを登録する
	 * 登録できるのは1つだけ
	 * @param listener EUSARTモジュールの割り込みリスナ
	 */
	void (*addInterruptListener)(EusartInterruptListener* listener);
	/**
	 * 受信割り込みを有効にする
	 */
	void (*enableRXInterrupt)(void);
	/**
	 * 受信割り込みを無効にする
	 */
	void (*disableRXInterrupt)(void);
	/**
	 * 送信割り込みを有効にする
	 */
	void (*enableTXInterrupt)(void);
	/**
	 * 送信割り込みを無効にする
	 */
	void (*disableTXInterrupt)(void);
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

/*
 * PICのEUSARTモジュールを操作するオブジェクト
 * とりあえずは使わない機能（同期通信など）を省いて、基本機能のみ抑える
 */

#ifndef EUSART_H
#define EUSART_H

typedef void (*EUSART_resetInterface)(void);
typedef void (*EUSART_setbaudRateInterface)(unsigned long baudRate);
typedef void (*EUSART_enableInterface)(void);
typedef void (*EUSART_disableInterface)(void);
typedef char (*EUSART_readInterface)(void);
typedef void (*EUSART_writeInterface)(char data);

// EUSARTのオブジェクト
// EUSART.cで実体を定義
typedef struct {
	/**
	 * 現在の設定のまま、シリアルポートをリセットする
	 * エラーで動作しない場合に呼び出すこと
	 */
	EUSART_resetInterface reset;
	/**
	 * ボーレートを設定する
	 * @param ボーレート、整数で指定
	 */
	EUSART_setbaudRateInterface setbaudRate;
	/**
	 * EUSARTを有効にする
	 */
	EUSART_enableInterface enable;
	/**
	 * EUSARTを無効にする
	 */
	EUSART_disableInterface disable;
	/**
	 * 1byte受信する
	 * @return 受信データ
	 */
	EUSART_readInterface read;
	/**
	 * 1byte送信する
	 * @param data 送信するデータ
	 */
	EUSART_writeInterface write;
} Eusart;

#endif /* EUSART_H */

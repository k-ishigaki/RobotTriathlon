/*
 * PICのEUSARTモジュールを操作するオブジェクト
 * とりあえずは使わない機能（同期通信など）を省いて、基本機能のみ抑える
 */

#ifndef EUSART_H
#define EUSART_H

typedef void (*EUSART_resetMethod)(void);
typedef void (*EUSART_setbaudRateMethod)(unsigned long baudRate);
typedef void (*EUSART_enableMethod)(void);
typedef void (*EUSART_disableMethod)(void);
typedef char (*EUSART_readMethod)(void);
typedef void (*EUSART_writeMethod)(char data);

// EUSARTのオブジェクト
// EUSART.cで実体を定義
typedef struct {
	/**
	 * 現在の設定のまま、シリアルポートをリセットする
	 * エラーで動作しない場合に呼び出すこと
	 */
	EUSART_resetMethod reset;
	/**
	 * ボーレートを設定する
	 * @param ボーレート、整数で指定
	 */
	EUSART_setbaudRateMethod setbaudRate;
	/**
	 * EUSARTを有効にする
	 */
	EUSART_enableMethod enable;
	/**
	 * EUSARTを無効にする
	 */
	EUSART_disableMethod disable;
	/**
	 * 1byte受信する
	 * @return 受信データ
	 */
	EUSART_readMethod read;
	/**
	 * 1byte送信する
	 * @param data 送信するデータ
	 */
	EUSART_writeMethod write;
} Eusart;

#endif /* EUSART_H */

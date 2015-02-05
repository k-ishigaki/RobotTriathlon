/*
 * PICのEUSARTモジュールを操作するオブジェクト
 * とりあえずは使わない機能（同期通信など）を省いて、基本機能のみ抑える
 */

#ifndef EUSART_H
#define EUSART_H

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
	 * @param ボーレート、整数で指定
	 */
	void (*setbaudRate)(unsigned long baudRate);
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
	unsigned char (*read)(void);
	/**
	 * 1byte送信する
	 * @param data 送信するデータ
	 */
	void (*write)(unsigned char);
} Eusart;

#endif /* EUSART_H */

/*
 * PICのEUSARTモジュールを操作するオブジェクト
 * まずgetEUSART関数でEUSARTのオブジェクトを取得し、
 * それを各メソッド(EUSART_*)の第一引数に指定する
 * PIC18F系で使いまわせるようなヘッダファイルにしたい
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
	char (*read)(void);
	/**
	 * 1byte送信する
	 * @param data 送信するデータ
	 */
	void (*write)(char data);
} Eusart;

/**
 * EUSARTのオブジェクトを返す
 * @return EUSARTの構造体ポインタ，取得できない場合はNULL
 */
Eusart* getEUSART(void);
Eusart* getEUSART1(void);
Eusart* getEUSART2(void);

#endif /* EUSART_H */

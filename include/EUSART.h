/*
 * PICのEUSARTモジュールを操作するオブジェクト
 * まずgetEUSART関数でEUSARTのオブジェクトを取得し、
 * それを各メソッド(EUSART_*)の第一引数に指定する
 * PIC18F系で使いまわせるようなヘッダファイルにしたい
 * とりあえずは使わない機能（同期通信など）を省いて、基本機能のみ抑える
 */

#ifndef EUSART_H
#define EUSART_H

#define PREFIX(name) EUSART_##name##Method

typedef void (*PREFIX(reset))(void);
typedef void (*PREFIX(setbaudRate))(unsigned long baudRate);
typedef void (*PREFIX(enable))(void);
typedef void (*PREFIX(disable))(void);
typedef char (*PREFIX(read))(void);
typedef void (*PREFIX(write))(char data);

// EUSARTのオブジェクト
// EUSART.cで実体を定義
typedef struct {
	/**
	 * 現在の設定のまま、シリアルポートをリセットする
	 * エラーで動作しない場合に呼び出すこと
	 */
	PREFIX(reset) reset;
	/**
	 * ボーレートを設定する
	 * @param ボーレート、整数で指定
	 */
	PREFIX(setbaudRate) setbaudRate;
	/**
	 * EUSARTを有効にする
	 */
	PREFIX(enable) enable;
	/**
	 * EUSARTを無効にする
	 */
	PREFIX(disable) disable;
	/**
	 * 1byte受信する
	 * @return 受信データ
	 */
	PREFIX(read) read;
	/**
	 * 1byte送信する
	 * @param data 送信するデータ
	 */
	PREFIX(write) write;
} Eusart;

/**
 * EUSARTのオブジェクトを返す
 * @return EUSARTの構造体ポインタ，取得できない場合はNULL
 */
Eusart* getEUSART(void);
Eusart* getEUSART1(void);
Eusart* getEUSART2(void);

#endif /* EUSART_H */

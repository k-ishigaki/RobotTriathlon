/*
 * PICのEUSARTモジュールを操作するオブジェクト
 * まずgetEUSART関数でEUSARTのオブジェクトを取得し、
 * それを各メソッド(EUSART_*)の第一引数に指定する
 * PIC18F系で使いまわせるようなヘッダファイルにしたい
 * とりあえずは使わない機能（同期通信など）を省いて、基本機能のみ抑える
 */

#ifndef EUSART_H
#define EUSART_H

// EUSARTのオブジェクト（構造体）
// EUSART.cの中で実態が定義されている
// Eusartの記述を簡略化するためにtypedef
typedef struct Eusart_t Eusart;

// EUSARTが複数ある場合に、getEUSART関数の引数に指定する
enum EusartIdentifier {
	EUSART1,
	EUSART2,
};

/**
 * EUSARTのオブジェクトを返す
 * @param e EUSARTの識別子（複数ある場合は選択する必要あり）
 * @return EUSARTのオブジェクト
 */
Eusart* getEUSART(enum EusartIdentifier e);

/**
 * ボーレートを設定し、ポートを開く
 * @param this EUSARTのオブジェクト
 * @param baudRate ボーレート、整数で指定
 * @return 開けなかった場合は0
 */
char EUSART_open(Eusart *this, long baudRate);

/**
 * 現在の設定のまま、シリアルポートをリセットする
 * エラーで動作しない場合に呼び出すこと
 * @param this EUSARTのオブジェクト
 */
void EUSART_reset(Eusart *this);

/**
 * ボーレートを設定する
 * @param EUSARTのオブジェクト
 * @param ボーレート、整数で指定
 * @return 設定できない値の場合は0
 */
char EUSART_setBaudRate(Eusart *this, unsigned long baudRate);

/**
 * 設定されているボーレートを取得する
 * @param this EUSARTのオブジェクト
 * @return ボーレート、整数値
 */
unsigned long EUSART_getBaudRate(Eusart *this);

/**
 * シリアルポートを有効にする
 * setBaudRateを実行していない場合はボーレートはデフォルト値となる
 * @param this EUSARTのオブジェクト
 */
void EUSART_enableSerialPort(Eusart *this);

/**
 * シリアルポートを無効にする
 * @param this EUSARTのオブジェクト
 */
void EUSART_disableSerialPort(Eusart *this);

/**
 * 受信割り込みを有効にする
 * @param this EUSARTのオブジェクト
 */
void EUSART_enableRXInterrupt(Eusart *this);

/**
 * 受信割り込みを無効にする
 * @param this EUSARTのオブジェクト
 */
void EUSART_disableRXInterrupt(Eusart *this);

/**
 * 送信割り込みを有効にする
 * @param this EUSARTのオブジェクト
 */
void EUSART_enableTXInterrupt(Eusart *this);

/**
 * 送信割り込みを無効にする
 * @param this EUSARTのオブジェクト
 */
void EUSART_disableTXInterrupt(Eusart *this);

/**
 * 1byte受信する
 * @pram this EUSARTのオブジェクト
 * @param data 受信データの格納先のポインタ
 * @return バッファに何もなかったら0
 */
char EUSART_receive(Eusart *this, char *data);

/**
 * 1byte送信する
 * @param this EUSARTのオブジェクト
 * @param data 送信するデータ
 * @return バッファがいっぱいだったら0
 */
char EUSART_transmit(Eusart *this, char data);

/**
 * 受信バッファにデータがあるかを確認する
 * @param this EUSARTのオブジェクト
 * @return データがある場合は1、ない場合は0
 */
char EUSART_Received(Eusart *this);

/**
 * 送信バッファが空かを確認する
 * @param this EUSARTのオブジェクト
 * @return 空の場合は1、空でない場合は0
 */
char EUSART_isTXBufferEmpty(Eusart *this);

#endif /* EUSART_H */

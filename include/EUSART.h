/*
 * PICのEUSARTモジュールを操作するオブジェクト
 * まずgetEUSART関数でEUSARTのオブジェクトを取得し、
 * それを各メソッド(EUSART_*)の第一引数に指定する
 * PIC18F系で使いまわせるようなヘッダファイルにしたい
 * とりあえずは使わない機能（同期通信など）を省いて、基本機能のみ抑える
 */

#ifndef EUSART_H
#define EUSART_H

// EUSARTの数
// ソースコードではNUM_OF_EUSARTを元に分岐を行っている
// チップ名によってNUM_OF_EUSARTを決定する
#if defined (_18F26K22)
#define NUM_OF_EUSART 2
#else
#error your device has no definition of NUM_OF_EUSART, \
please add definition of your device here.
#endif

// EUSARTのオブジェクト（構造体）
// EUSART.cの中で実態が定義されている
// Eusartの記述を簡略化するためにtypedef
typedef struct Eusart_t Eusart;

// EUSARTが複数ある場合に、getEUSART関数の引数に指定する
enum EusartIdentifier {
#if NUM_OF_EUSART == 1
	EUSART,
#elif NUM_OF_EUSART == 2
	EUSART1,
	EUSART2,
#endif
};

/**
 * EUSARTのオブジェクトを返す
 * @param e EUSARTの識別子（複数ある場合は選択する必要あり）
 * @return EUSARTのオブジェクト
 */
Eusart* getEUSART(enum EusartIdentifier e);

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

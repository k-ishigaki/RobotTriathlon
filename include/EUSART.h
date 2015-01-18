/*
 * PICのEUSARTモジュールを操作するオブジェクト
 * まずgetEUSART関数でEUSARTのオブジェクトを取得し、
 * それを各メソッド(EUSART_*)の第一引数に指定する
 * PIC18F系で使いまわせるようなヘッダファイルにしたい
 * とりあえずは使わない機能（同期通信など）を省いて、基本機能のみ抑える
 */

#include <stdint.h>
#include <stdbool.h>

#ifndef EUSART_H
#define EUSART_H

// EUSARTの数
// ソースコードではNUM_OF_EUSARTを元に分岐を行っている
// チップ名によってNUM_OF_EUSARTを決定する
#if defined (_18F26K22)
#define NUM_OF_EUSART 2
#else
#error please add definition of your device here.
#endif

// EUSARTのオブジェクト
// EUSART.cで実体を定義
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
 * @return EUSARTの構造体ポインタ，取得できない場合はNULL
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
bool EUSART_setBaudRate(Eusart *this, uint_fast32_t baudRate);

/**
 * EUSARTを有効にする
 * @param this EUSARTのオブジェクト
 */
void EUSART_enable(Eusart *this);

/**
 * EUSARTを無効にする
 * @param this EUSARTのオブジェクト
 */
void EUSART_disable(Eusart *this);

/**
 * 1byte受信する
 * @pram this EUSARTのオブジェクト
 * @return 受信データ
 */
uint_fast8_t EUSART_read(Eusart *this);

/**
 * 1byte送信する
 * @param this EUSARTのオブジェクト
 * @param data 送信するデータ
 */
void EUSART_write(Eusart *this, uint_fast8_t data);

#endif /* EUSART_H */

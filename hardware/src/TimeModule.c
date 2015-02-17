/*
 * Timer Moduleの実体定義
 * 3種類のタイマ(8bit, 16bit, それ以外)の実装を記述する
 * このファイルにはレジスタ定義などを，substance.cファイルで
 * 定義ごとに分岐して実装を記述している
 */
#include "Hardware.h"

#define USING_TIMER_MODULE_SUBSTANCE

// Timer1
// include substance.c as 16bit timer
#define IS_16BIT_TIMER
// register
#define Timer1_TxCON T1CONbits
#define Timer1_TMRxL TMR1Lbits
#define Timer1_TMRxH TMR1Hbits
#define Timer1_PIEx PIE1bits
#define Timer1_PIRx PIR1bits
#define Timer1_IPRx IPR1bits
// getter function name
#define Timer1_getter getTimer1
// string concatenation
#define NAMESPACE(name) Timer1_##name
#define TMRx(name) TMR1##name
#define Tx(name) T1##name

#include "TimerModule.substance.c"

// Timer3
// include substance.c as 16bit timer
#define IS_16BIT_TIMER
// register
#define Timer3_TxCON T3CONbits
#define Timer3_TMRxL TMR3Lbits
#define Timer3_TMRxH TMR3Hbits
#define Timer3_PIEx PIE2bits
#define Timer3_PIRx PIR2bits
#define Timer3_IPRx IPR2bits
// getter function name
#define Timer3_getter getTimer3
// string concatenation
#define NAMESPACE(name) Timer3_##name
#define TMRx(name) TMR3##name
#define Tx(name) T3##name

#include "TimerModule.substance.c"

// Timer5
// include substance.c as 16bit timer
#define IS_16BIT_TIMER
// register
#define Timer5_TxCON T5CONbits
#define Timer5_TMRxL TMR5Lbits
#define Timer5_TMRxH TMR5Hbits
#define Timer5_PIEx PIE5bits
#define Timer5_PIRx PIR5bits
#define Timer5_IPRx IPR5bits
// getter function name
#define Timer5_getter getTimer5
// string concatenation
#define NAMESPACE(name) Timer5_##name
#define TMRx(name) TMR5##name
#define Tx(name) T5##name

#include "TimerModule.substance.c"


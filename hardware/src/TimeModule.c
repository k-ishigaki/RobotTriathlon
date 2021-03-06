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

// Timer2
// include substance.c as 8bit timer
#define IS_8BIT_TIMER
// register
#define Timer2_TxCON T2CONbits
#define Timer2_TMRx TMR2bits.TMR2
#define Timer2_PRx PR2bits.PR2
#define Timer2_PIEx PIE1bits
#define Timer2_PIRx PIR1bits
#define Timer2_IPRx IPR1bits
// getter function name
#define Timer2_getter getTimer2
// string concatenation
#define NAMESPACE(name) Timer2_##name
#define TMRx(name) TMR2##name
#define Tx(name) T2##name

#include "TimerModule.substance.c"

// Timer4
// include substance.c as 8bit timer
#define IS_8BIT_TIMER
// register
#define Timer4_TxCON T4CONbits
#define Timer4_TMRx TMR4bits.TMR4
#define Timer4_PRx PR4bits.PR4
#define Timer4_PIEx PIE5bits
#define Timer4_PIRx PIR5bits
#define Timer4_IPRx IPR5bits
// getter function name
#define Timer4_getter getTimer4
// string concatenation
#define NAMESPACE(name) Timer4_##name
#define TMRx(name) TMR4##name
#define Tx(name) T4##name

#include "TimerModule.substance.c"

// Timer6
// include substance.c as 8bit timer
#define IS_8BIT_TIMER
// register
#define Timer6_TxCON T6CONbits
#define Timer6_TMRx TMR6bits.TMR6
#define Timer6_PRx PR6bits.PR6
#define Timer6_PIEx PIE5bits
#define Timer6_PIRx PIR5bits
#define Timer6_IPRx IPR5bits
// getter function name
#define Timer6_getter getTimer6
// string concatenation
#define NAMESPACE(name) Timer6_##name
#define TMRx(name) TMR6##name
#define Tx(name) T6##name

#include "TimerModule.substance.c"

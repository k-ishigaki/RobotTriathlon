/*
 * Timer Moduleの実体定義
 * 3種類のタイマ(8bit, 16bit, 両方対応)の実装を記述する
 * このファイルにはレジスタ定義などを，substance.cファイルで
 * 定義ごとに分岐して実装を記述している
 */
#include "Hardware.h"

#define USING_TIMER_MODULE_SUBSTANCE

// Timer1
#define IS_16BIT_TIMER
#define TIMER1_txcon T1CONbits
#define TIMER1_tmrl TMR1L
#define TIMER1_tmrh TMR1H
#define TIMER1_ie PIE1bits.TMR1IE
#define TIMER1_if PIR1bits.TMR1IF
#define NAMESPACE(name) TIMER1_##name

#include "TimerModule.substance.c"





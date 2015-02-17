/*
 * EUSARTモジュールの実体を定義する
 * それぞれのインスタンスで共有するコードはEUSART.substance.cに記述する
 * .substance.cファイルの中で利用される変数はこのファイルで割り当てるが、
 * 変数名の衝突が起こらないようにNAMESPACEマクロを用いている
 */
#include <xc.h>
#include "Hardware.h"

// EUSARTの実体を利用する
// EUSART.substance.cをインクルードするのに必要
#define USING_EUSART_SUBSTANCE

// Eusart1
// register
#define EUSART1_RCSTAx RCSTA1bits
#define EUSART1_TXSTAx TXSTA1bits
#define EUSART1_BAUDCONx BAUDCON1bits
#define EUSART1_SPBRGx SPBRG1bits
#define EUSART1_SPBRGHx SPBRGH1bits
#define EUSART1_RCREGx RCREG1bits
#define EUSART1_TXREGx TXREG1bits
#define EUSART1_PIRx PIR1bits
#define EUSART1_PIEx PIE1bits
#define EUSART1_IPRx IPR1bits
// getter function name
#define EUSART1_getter getEUSART1
// string concatenation
#define RCx(name) RC1##name
#define TXx(name) TX1##name
#define SPx(name) SP1##name
#define NAMESPACE(name) EUSART1_##name

#include "EUSART.substance.c"

// Eusart2
// register
#define EUSART2_RCSTAx RCSTA2bits
#define EUSART2_TXSTAx TXSTA2bits
#define EUSART2_BAUDCONx BAUDCON2bits
#define EUSART2_SPBRGx SPBRG2bits
#define EUSART2_SPBRGHx SPBRGH2bits
#define EUSART2_RCREGx RCREG2bits
#define EUSART2_TXREGx TXREG2bits
#define EUSART2_PIRx PIR3bits
#define EUSART2_PIEx PIE3bits
#define EUSART2_IPRx IPR3bits
// getter function name
#define EUSART2_getter getEUSART2
// string concatenation
#define RCx(name) RC2##name
#define TXx(name) TX2##name
#define SPx(name) SP2##name
#define NAMESPACE(name) EUSART2_##name

#include "EUSART.substance.c"


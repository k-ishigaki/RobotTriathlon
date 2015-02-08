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

#define EUSART1_rcsta RCSTA1bits
#define EUSART1_txsta TXSTA1bits
#define EUSART1_baudcon BAUDCON1bits
#define EUSART1_spbrg SPBRG1
#define EUSART1_spbrgh SPBRGH1
#define EUSART1_rcreg RCREG1
#define EUSART1_txreg TXREG1

#define EUSART2_rcsta RCSTA2bits
#define EUSART2_txsta TXSTA2bits
#define EUSART2_baudcon BAUDCON2bits
#define EUSART2_spbrg SPBRG2
#define EUSART2_spbrgh SPBRGH2
#define EUSART2_rcreg RCREG2
#define EUSART2_txreg TXREG2

#define NAMESPACE(name) EUSART1_##name
#include "EUSART.substance.c"
Eusart* getEUSART() {
	return (Eusart*)&NAMESPACE(eusart);
}
Eusart* getEUSART1() {
	return (Eusart*)&NAMESPACE(eusart);
}

#undef NAMESPACE
#define NAMESPACE(name) EUSART2_##name
#include "EUSART.substance.c"
Eusart* getEUSART2() {
	return (Eusart*)&NAMESPACE(eusart);
}

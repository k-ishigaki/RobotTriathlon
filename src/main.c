#include <xc.h>	// xc8 projects must use this header file
#include "Hardware.h"
#include "EUSART.h"
/**
 * ロボットトライアスロン用のプログラム
 */
int main(void) {	// use int type for CCI interface
	Eusart* serial = (Eusart*)getEUSART1;
	serial->reset();
	di();	// disable interrupt
	ei();	// enable interrupt
}

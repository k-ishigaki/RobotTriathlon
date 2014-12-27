#include <xc.h>	// xc8 projects must use this header file
#include "configurationBits.h"	// configuration bits are defined in this header file
/**
 * @brief ロボットトライアスロン用のプログラム
 */
int main(void){	// use int type for CCI interface
	ei();	// enable interrupt
	di();	// disable interrupt
}

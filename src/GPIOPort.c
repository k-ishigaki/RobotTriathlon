/*
 * GPIO PORTモジュールの実体を定義する
 * それぞれのインスタンスで共有するコードはGPIOPort.substance.cに記述する
 * .substance.cファイルの中で利用される変数はこのファイルで割り当てるが、
 * 変数名の衝突が起こらないようにNAMESPACEマクロを用いている
 */
#include <xc.h>
#include "Hardware.h"
#include "GPIOPort.h"

#define USING_GPIO_PORT_SUBSTANCE

#define NAMESPACE(name) PORTA_##name
volatile unsigned char* NAMESPACE(ansel) = &ANSELA;
volatile unsigned char* NAMESPACE(tris) = &TRISA;
volatile unsigned char* NAMESPACE(port) = &PORTA;
volatile unsigned char* NAMESPACE(lat) = &LATA;

#include "GPIOPort.substance.c"

GPIOPort* getPORTA() {
	return (GPIOPort*)&NAMESPACE(gpioPort);
}





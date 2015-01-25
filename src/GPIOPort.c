/*
 * GPIO PORTモジュールの実体を定義する
 * それぞれのインスタンスで共有するコードはGPIOPort.substance.cに記述する
 * .substance.cファイルの中で利用される変数はこのファイルで割り当てるが、
 * 変数名の衝突が起こらないようにNAMESPACEマクロを用いている
 */
#include <xc.h>
#include "Hardware.h"

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

#undef NAMESPACE

#define NAMESPACE(name) PORTB_##name
volatile unsigned char* NAMESPACE(ansel) = &ANSELB;
volatile unsigned char* NAMESPACE(tris) = &TRISB;
volatile unsigned char* NAMESPACE(port) = &PORTB;
volatile unsigned char* NAMESPACE(lat) = &LATB;

#include "GPIOPort.substance.c"

GPIOPort* getPORTB() {
	return (GPIOPort*)&NAMESPACE(gpioPort);
}

#undef NAMESPACE

#define NAMESPACE(name) PORTC_##name
volatile unsigned char* NAMESPACE(ansel) = &ANSELC;
volatile unsigned char* NAMESPACE(tris) = &TRISC;
volatile unsigned char* NAMESPACE(port) = &PORTC;
volatile unsigned char* NAMESPACE(lat) = &LATC;

#include "GPIOPort.substance.c"

GPIOPort* getPORTC() {
	return (GPIOPort*)&NAMESPACE(gpioPort);
}

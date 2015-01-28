/*
 * GPIO PORTモジュールの実体を定義する
 * それぞれのインスタンスで共有するコードはGPIOPort.substance.cに記述する
 * .substance.cファイルの中で利用される変数はこのファイルで割り当てるが、
 * 変数名の衝突が起こらないようにNAMESPACEマクロを用いている
 */
#include <xc.h>
#include "Hardware.h"

#define USING_GPIO_PORT_SUBSTANCE

#define PORTA_ansel ANSELA
#define PORTA_tris TRISA
#define PORTA_port PORTA
#define PORTA_lat LATA
#define PORTB_ansel ANSELB
#define PORTB_tris TRISB
#define PORTB_port PORTB
#define PORTB_lat LATB
#define PORTC_ansel ANSELC
#define PORTC_tris TRISC
#define PORTC_port PORTC
#define PORTC_lat LATC

#define NAMESPACE(name) PORTA_##name

#include "GPIOPort.substance.c"

GPIOPort* getPORTA() {
	return (GPIOPort*)&NAMESPACE(gpioPort);
}

#undef NAMESPACE
#define NAMESPACE(name) PORTB_##name

#include "GPIOPort.substance.c"

GPIOPort* getPORTB() {
	return (GPIOPort*)&NAMESPACE(gpioPort);
}

#undef NAMESPACE
#define NAMESPACE(name) PORTC_##name

#include "GPIOPort.substance.c"

GPIOPort* getPORTC() {
	return (GPIOPort*)&NAMESPACE(gpioPort);
}

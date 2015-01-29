/*
 * GPIOピンの実体を定義
 * 1つ1つのピンの実体をすべて定義する
 */
#include <xc.h>
#include "Hardware.h"

#define USING_GPIO_PIN_SUBSTANCE

#define RA0_tris TRISAbits.TRISA0
#define RA0_ansel ANSELAbits.ANSA0
#define RA0_port PORTAbits.RA0
#define RA0_lat LATAbits.LATA0

#undef NAMESPACE
#define NAMESPACE(name) RA0_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"



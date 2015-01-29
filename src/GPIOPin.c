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

#define RA1_tris TRISAbits.TRISA1
#define RA1_ansel ANSELAbits.ANSA1
#define RA1_port PORTAbits.RA1
#define RA1_lat LATAbits.LATA1

#define RA2_tris TRISAbits.TRISA2
#define RA2_ansel ANSELAbits.ANSA2
#define RA2_port PORTAbits.RA2
#define RA2_lat LATAbits.LATA2

#define RA3_tris TRISAbits.TRISA3
#define RA3_ansel ANSELAbits.ANSA3
#define RA3_port PORTAbits.RA3
#define RA3_lat LATAbits.LATA3

#define RA4_tris TRISAbits.TRISA4
#define RA4_port PORTAbits.RA4
#define RA4_lat LATAbits.LATA4

#define RA5_tris TRISAbits.TRISA5
#define RA5_ansel ANSELAbits.ANSA5
#define RA5_port PORTAbits.RA5
#define RA5_lat LATAbits.LATA5

#define RA6_tris TRISAbits.TRISA6
#define RA6_port PORTAbits.RA6
#define RA6_lat LATAbits.LATA6

#define RA7_tris TRISAbits.TRISA7
#define RA7_port PORTAbits.RA7
#define RA7_lat LATAbits.LATA7

#undef NAMESPACE
#define NAMESPACE(name) RA0_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRA0() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RA1_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRA1() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RA2_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRA2() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RA3_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRA3() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RA4_##name
#include "GPIOPin.substance.c"
GPIOPin* getRA4() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RA5_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRA5() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RA6_##name
#include "GPIOPin.substance.c"
GPIOPin* getRA6() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RA7_##name
#include "GPIOPin.substance.c"
GPIOPin* getRA7() {
	return &NAMESPACE(gpioPin);
}

#define RB0_tris TRISBbits.TRISB0
#define RB0_ansel ANSELBbits.ANSB0
#define RB0_port PORTBbits.RB0
#define RB0_lat LATBbits.LATB0

#define RB1_tris TRISBbits.TRISB1
#define RB1_ansel ANSELBbits.ANSB1
#define RB1_port PORTBbits.RB1
#define RB1_lat LATBbits.LATB1

#define RB2_tris TRISBbits.TRISB2
#define RB2_ansel ANSELBbits.ANSB2
#define RB2_port PORTBbits.RB2
#define RB2_lat LATBbits.LATB2

#define RB3_tris TRISBbits.TRISB3
#define RB3_ansel ANSELBbits.ANSB3
#define RB3_port PORTBbits.RB3
#define RB3_lat LATBbits.LATB3

#define RB4_tris TRISBbits.TRISB4
#define RB4_ansel ANSELBbits.ANSB4
#define RB4_port PORTBbits.RB4
#define RB4_lat LATBbits.LATB4

#define RB5_tris TRISBbits.TRISB5
#define RB5_ansel ANSELBbits.ANSB5
#define RB5_port PORTBbits.RB5
#define RB5_lat LATBbits.LATB5

#define RB6_tris TRISBbits.TRISB6
#define RB6_port PORTBbits.RB6
#define RB6_lat LATBbits.LATB6

#define RB7_tris TRISBbits.TRISB7
#define RB7_port PORTBbits.RB7
#define RB7_lat LATBbits.LATB7

#undef NAMESPACE
#define NAMESPACE(name) RB0_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRB0() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RB1_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRB1() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RB2_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRB2() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RB3_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRB3() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RB4_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRB4() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RB5_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRB5() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RB6_##name
#include "GPIOPin.substance.c"
GPIOPin* getRB6() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RB7_##name
#include "GPIOPin.substance.c"
GPIOPin* getRB7() {
	return &NAMESPACE(gpioPin);
}

#define RC0_tris TRISCbits.TRISC0
#define RC0_port PORTCbits.RC0
#define RC0_lat LATCbits.LATC0

#define RC1_tris TRISCbits.TRISC1
#define RC1_port PORTCbits.RC1
#define RC1_lat LATCbits.LATC1

#define RC2_tris TRISCbits.TRISC2
#define RC2_ansel ANSELCbits.ANSC2
#define RC2_port PORTCbits.RC2
#define RC2_lat LATCbits.LATC2

#define RC3_tris TRISCbits.TRISC3
#define RC3_ansel ANSELCbits.ANSC3
#define RC3_port PORTCbits.RC3
#define RC3_lat LATCbits.LATC3

#define RC4_tris TRISCbits.TRISC4
#define RC4_ansel ANSELCbits.ANSC4
#define RC4_port PORTCbits.RC4
#define RC4_lat LATCbits.LATC4

#define RC5_tris TRISCbits.TRISC5
#define RC5_ansel ANSELCbits.ANSC5
#define RC5_port PORTCbits.RC5
#define RC5_lat LATCbits.LATC5

#define RC6_tris TRISCbits.TRISC6
#define RC6_ansel ANSELCbits.ANSC6
#define RC6_port PORTCbits.RC6
#define RC6_lat LATCbits.LATC6

#define RC7_tris TRISCbits.TRISC7
#define RC7_ansel ANSELCbits.ANSC7
#define RC7_port PORTCbits.RC7
#define RC7_lat LATCbits.LATC7

#undef NAMESPACE
#define NAMESPACE(name) RC0_##name
#include "GPIOPin.substance.c"
GPIOPin* getRC0() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RC1_##name
#include "GPIOPin.substance.c"
GPIOPin* getRC1() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RC2_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRC2() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RC3_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRC3() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RC4_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRC4() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RC5_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRC5() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RC6_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRC6() {
	return &NAMESPACE(gpioPin);
}

#undef NAMESPACE
#define NAMESPACE(name) RC7_##name
#define HAS_ANALOG_INTERFACE
#include "GPIOPin.substance.c"
GPIOPin* getRC7() {
	return &NAMESPACE(gpioPin);
}


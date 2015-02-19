/*
 * GPIOピンの実体を定義
 * 1つ1つのピンの実体をすべて定義する
 */
#include <xc.h>
#include "Hardware.h"

#define USING_GPIO_PIN_SUBSTANCE

#define RA0_TRISx TRISAbits.TRISA0
#define RA0_ANSELx ANSELAbits.ANSA0
#define RA0_PORTx PORTAbits.RA0
#define RA0_LATx LATAbits.LATA0

#define RA1_TRISx TRISAbits.TRISA1
#define RA1_ANSELx ANSELAbits.ANSA1
#define RA1_PORTx PORTAbits.RA1
#define RA1_LATx LATAbits.LATA1

#define RA2_TRISx TRISAbits.TRISA2
#define RA2_ANSELx ANSELAbits.ANSA2
#define RA2_PORTx PORTAbits.RA2
#define RA2_LATx LATAbits.LATA2

#define RA3_TRISx TRISAbits.TRISA3
#define RA3_ANSELx ANSELAbits.ANSA3
#define RA3_PORTx PORTAbits.RA3
#define RA3_LATx LATAbits.LATA3

#define RA4_TRISx TRISAbits.TRISA4
#define RA4_PORTx PORTAbits.RA4
#define RA4_LATx LATAbits.LATA4

#define RA5_TRISx TRISAbits.TRISA5
#define RA5_ANSELx ANSELAbits.ANSA5
#define RA5_PORTx PORTAbits.RA5
#define RA5_LATx LATAbits.LATA5

#define RA6_TRISx TRISAbits.TRISA6
#define RA6_PORTx PORTAbits.RA6
#define RA6_LATx LATAbits.LATA6

#define RA7_TRISx TRISAbits.TRISA7
#define RA7_PORTx PORTAbits.RA7
#define RA7_LATx LATAbits.LATA7

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

#define RB0_TRISx TRISBbits.TRISB0
#define RB0_ANSELx ANSELBbits.ANSB0
#define RB0_PORTx PORTBbits.RB0
#define RB0_LATx LATBbits.LATB0

#define RB1_TRISx TRISBbits.TRISB1
#define RB1_ANSELx ANSELBbits.ANSB1
#define RB1_PORTx PORTBbits.RB1
#define RB1_LATx LATBbits.LATB1

#define RB2_TRISx TRISBbits.TRISB2
#define RB2_ANSELx ANSELBbits.ANSB2
#define RB2_PORTx PORTBbits.RB2
#define RB2_LATx LATBbits.LATB2

#define RB3_TRISx TRISBbits.TRISB3
#define RB3_ANSELx ANSELBbits.ANSB3
#define RB3_PORTx PORTBbits.RB3
#define RB3_LATx LATBbits.LATB3

#define RB4_TRISx TRISBbits.TRISB4
#define RB4_ANSELx ANSELBbits.ANSB4
#define RB4_PORTx PORTBbits.RB4
#define RB4_LATx LATBbits.LATB4

#define RB5_TRISx TRISBbits.TRISB5
#define RB5_ANSELx ANSELBbits.ANSB5
#define RB5_PORTx PORTBbits.RB5
#define RB5_LATx LATBbits.LATB5

#define RB6_TRISx TRISBbits.TRISB6
#define RB6_PORTx PORTBbits.RB6
#define RB6_LATx LATBbits.LATB6

#define RB7_TRISx TRISBbits.TRISB7
#define RB7_PORTx PORTBbits.RB7
#define RB7_LATx LATBbits.LATB7

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

#define RC0_TRISx TRISCbits.TRISC0
#define RC0_PORTx PORTCbits.RC0
#define RC0_LATx LATCbits.LATC0

#define RC1_TRISx TRISCbits.TRISC1
#define RC1_PORTx PORTCbits.RC1
#define RC1_LATx LATCbits.LATC1

#define RC2_TRISx TRISCbits.TRISC2
#define RC2_ANSELx ANSELCbits.ANSC2
#define RC2_PORTx PORTCbits.RC2
#define RC2_LATx LATCbits.LATC2

#define RC3_TRISx TRISCbits.TRISC3
#define RC3_ANSELx ANSELCbits.ANSC3
#define RC3_PORTx PORTCbits.RC3
#define RC3_LATx LATCbits.LATC3

#define RC4_TRISx TRISCbits.TRISC4
#define RC4_ANSELx ANSELCbits.ANSC4
#define RC4_PORTx PORTCbits.RC4
#define RC4_LATx LATCbits.LATC4

#define RC5_TRISx TRISCbits.TRISC5
#define RC5_ANSELx ANSELCbits.ANSC5
#define RC5_PORTx PORTCbits.RC5
#define RC5_LATx LATCbits.LATC5

#define RC6_TRISx TRISCbits.TRISC6
#define RC6_ANSELx ANSELCbits.ANSC6
#define RC6_PORTx PORTCbits.RC6
#define RC6_LATx LATCbits.LATC6

#define RC7_TRISx TRISCbits.TRISC7
#define RC7_ANSELx ANSELCbits.ANSC7
#define RC7_PORTx PORTCbits.RC7
#define RC7_LATx LATCbits.LATC7

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


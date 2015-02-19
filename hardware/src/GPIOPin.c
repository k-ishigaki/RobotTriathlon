/*
 * GPIOピンの実体を定義
 * 1つ1つのピンの実体をすべて定義する
 */
#include <xc.h>
#include "Hardware.h"

#define USING_GPIO_PIN_SUBSTANCE

#define TRISxx xx(TRIS)
#define ANSxx xx(ANS)
#define LATxx xx(LAT)
#define Rxx xx(R)
#define WPUxx xx(WPU)

// RA0
#define HAS_ANALOG_INTERFACE
// register
#define RA0_TRISx TRISAbits
#define RA0_ANSELx ANSELAbits
#define RA0_PORTx PORTAbits
#define RA0_LATx LATAbits
// getter function name
#define RA0_getter getRA0
// string concatenation
#define NAMESPACE(name) RA0_##name
#define xx(name) name##A0
#include "GPIOPin.substance.c"

// RA1
#define HAS_ANALOG_INTERFACE
// register
#define RA1_TRISx TRISAbits
#define RA1_ANSELx ANSELAbits
#define RA1_PORTx PORTAbits
#define RA1_LATx LATAbits
// getter function name
#define RA1_getter getRA1
// string concatenation
#define NAMESPACE(name) RA1_##name
#define xx(name) name##A1
#include "GPIOPin.substance.c"

// RA2
#define HAS_ANALOG_INTERFACE
// register
#define RA2_TRISx TRISAbits
#define RA2_ANSELx ANSELAbits
#define RA2_PORTx PORTAbits
#define RA2_LATx LATAbits
// getter function name
#define RA2_getter getRA2
// string concatenation
#define NAMESPACE(name) RA2_##name
#define xx(name) name##A2
#include "GPIOPin.substance.c"

// RA3
#define HAS_ANALOG_INTERFACE
// register
#define RA3_TRISx TRISAbits
#define RA3_ANSELx ANSELAbits
#define RA3_PORTx PORTAbits
#define RA3_LATx LATAbits
// getter function name
#define RA3_getter getRA3
// string concatenation
#define NAMESPACE(name) RA3_##name
#define xx(name) name##A3
#include "GPIOPin.substance.c"

// RA4
// register
#define RA4_TRISx TRISAbits
#define RA4_PORTx PORTAbits
#define RA4_LATx LATAbits
// getter function name
#define RA4_getter getRA4
// string concatenation
#define NAMESPACE(name) RA4_##name
#define xx(name) name##A4
#include "GPIOPin.substance.c"

// RA5
#define HAS_ANALOG_INTERFACE
// register
#define RA5_TRISx TRISAbits
#define RA5_ANSELx ANSELAbits
#define RA5_PORTx PORTAbits
#define RA5_LATx LATAbits
// getter function name
#define RA5_getter getRA5
// string concatenation
#define NAMESPACE(name) RA5_##name
#define xx(name) name##A5
#include "GPIOPin.substance.c"

// RA6
// register
#define RA6_TRISx TRISAbits
#define RA6_PORTx PORTAbits
#define RA6_LATx LATAbits
// getter function name
#define RA6_getter getRA6
// string concatenation
#define NAMESPACE(name) RA6_##name
#define xx(name) name##A6
#include "GPIOPin.substance.c"

// RA7
// register
#define RA7_TRISx TRISAbits
#define RA7_PORTx PORTAbits
#define RA7_LATx LATAbits
// getter function name
#define RA7_getter getRA7
// string concatenation
#define NAMESPACE(name) RA7_##name
#define xx(name) name##A7
#include "GPIOPin.substance.c"

// RB0
#define HAS_ANALOG_INTERFACE
#define HAS_WEAK_INTERNAL_PULLUP
// register
#define RB0_TRISx TRISBbits
#define RB0_ANSELx ANSELBbits
#define RB0_PORTx PORTBbits
#define RB0_LATx LATBbits
#define RB0_WPUx WPUBbits
// getter function name
#define RB0_getter getRB0
// string concatenation
#define NAMESPACE(name) RB0_##name
#define xx(name) name##B0
#include "GPIOPin.substance.c"

// RB1
#define HAS_ANALOG_INTERFACE
#define HAS_WEAK_INTERNAL_PULLUP
// register
#define RB1_TRISx TRISBbits
#define RB1_ANSELx ANSELBbits
#define RB1_PORTx PORTBbits
#define RB1_LATx LATBbits
#define RB1_WPUx WPUBbits
// getter function name
#define RB1_getter getRB1
// string concatenation
#define NAMESPACE(name) RB1_##name
#define xx(name) name##B1
#include "GPIOPin.substance.c"

// RB2
#define HAS_ANALOG_INTERFACE
#define HAS_WEAK_INTERNAL_PULLUP
// register
#define RB2_TRISx TRISBbits
#define RB2_ANSELx ANSELBbits
#define RB2_PORTx PORTBbits
#define RB2_LATx LATBbits
#define RB2_WPUx WPUBbits
// getter function name
#define RB2_getter getRB2
// string concatenation
#define NAMESPACE(name) RB2_##name
#define xx(name) name##B2
#include "GPIOPin.substance.c"

// RB3
#define HAS_ANALOG_INTERFACE
#define HAS_WEAK_INTERNAL_PULLUP
// register
#define RB3_TRISx TRISBbits
#define RB3_ANSELx ANSELBbits
#define RB3_PORTx PORTBbits
#define RB3_LATx LATBbits
#define RB3_WPUx WPUBbits
// getter function name
#define RB3_getter getRB3
// string concatenation
#define NAMESPACE(name) RB3_##name
#define xx(name) name##B3
#include "GPIOPin.substance.c"

// RB4
#define HAS_ANALOG_INTERFACE
#define HAS_WEAK_INTERNAL_PULLUP
// register
#define RB4_TRISx TRISBbits
#define RB4_ANSELx ANSELBbits
#define RB4_PORTx PORTBbits
#define RB4_LATx LATBbits
#define RB4_WPUx WPUBbits
// getter function name
#define RB4_getter getRB4
// string concatenation
#define NAMESPACE(name) RB4_##name
#define xx(name) name##B4
#include "GPIOPin.substance.c"

// RB5
#define HAS_ANALOG_INTERFACE
#define HAS_WEAK_INTERNAL_PULLUP
// register
#define RB5_TRISx TRISBbits
#define RB5_ANSELx ANSELBbits
#define RB5_PORTx PORTBbits
#define RB5_LATx LATBbits
#define RB5_WPUx WPUBbits
// getter function name
#define RB5_getter getRB5
// string concatenation
#define NAMESPACE(name) RB5_##name
#define xx(name) name##B5
#include "GPIOPin.substance.c"

// RB6
#define HAS_WEAK_INTERNAL_PULLUP
// register
#define RB6_TRISx TRISBbits
#define RB6_PORTx PORTBbits
#define RB6_LATx LATBbits
#define RB6_WPUx WPUBbits
// getter function name
#define RB6_getter getRB6
// string concatenation
#define NAMESPACE(name) RB6_##name
#define xx(name) name##B6
#include "GPIOPin.substance.c"

// RB7
#define HAS_WEAK_INTERNAL_PULLUP
// register
#define RB7_TRISx TRISBbits
#define RB7_PORTx PORTBbits
#define RB7_LATx LATBbits
#define RB7_WPUx WPUBbits
// getter function name
#define RB7_getter getRB7
// string concatenation
#define NAMESPACE(name) RB7_##name
#define xx(name) name##B7
#include "GPIOPin.substance.c"

// RC0
// register
#define RC0_TRISx TRISCbits
#define RC0_PORTx PORTCbits
#define RC0_LATx LATCbits
// getter function name
#define RC0_getter getRC0
// string concatenation
#define NAMESPACE(name) RC0_##name
#define xx(name) name##C0
#include "GPIOPin.substance.c"

// RC1
// register
#define RC1_TRISx TRISCbits
#define RC1_PORTx PORTCbits
#define RC1_LATx LATCbits
// getter function name
#define RC1_getter getRC1
// string concatenation
#define NAMESPACE(name) RC1_##name
#define xx(name) name##C1
#include "GPIOPin.substance.c"

// RC2
#define HAS_ANALOG_INTERFACE
// register
#define RC2_TRISx TRISCbits
#define RC2_ANSELx ANSELCbits
#define RC2_PORTx PORTCbits
#define RC2_LATx LATCbits
// getter function name
#define RC2_getter getRC2
// string concatenation
#define NAMESPACE(name) RC2_##name
#define xx(name) name##C2
#include "GPIOPin.substance.c"

// RC3
#define HAS_ANALOG_INTERFACE
// register
#define RC3_TRISx TRISCbits
#define RC3_ANSELx ANSELCbits
#define RC3_PORTx PORTCbits
#define RC3_LATx LATCbits
// getter function name
#define RC3_getter getRC3
// string concatenation
#define NAMESPACE(name) RC3_##name
#define xx(name) name##C3
#include "GPIOPin.substance.c"

// RC4
#define HAS_ANALOG_INTERFACE
// register
#define RC4_TRISx TRISCbits
#define RC4_ANSELx ANSELCbits
#define RC4_PORTx PORTCbits
#define RC4_LATx LATCbits
// getter function name
#define RC4_getter getRC4
// string concatenation
#define NAMESPACE(name) RC4_##name
#define xx(name) name##C4
#include "GPIOPin.substance.c"

// RC5
#define HAS_ANALOG_INTERFACE
// register
#define RC5_TRISx TRISCbits
#define RC5_ANSELx ANSELCbits
#define RC5_PORTx PORTCbits
#define RC5_LATx LATCbits
// getter function name
#define RC5_getter getRC5
// string concatenation
#define NAMESPACE(name) RC5_##name
#define xx(name) name##C5
#include "GPIOPin.substance.c"

// RC6
#define HAS_ANALOG_INTERFACE
// register
#define RC6_TRISx TRISCbits
#define RC6_ANSELx ANSELCbits
#define RC6_PORTx PORTCbits
#define RC6_LATx LATCbits
// getter function name
#define RC6_getter getRC6
// string concatenation
#define NAMESPACE(name) RC6_##name
#define xx(name) name##C6
#include "GPIOPin.substance.c"

// RC7
#define HAS_ANALOG_INTERFACE
// register
#define RC7_TRISx TRISCbits
#define RC7_ANSELx ANSELCbits
#define RC7_PORTx PORTCbits
#define RC7_LATx LATCbits
// getter function name
#define RC7_getter getRC7
// string concatenation
#define NAMESPACE(name) RC7_##name
#define xx(name) name##C7
#include "GPIOPin.substance.c"


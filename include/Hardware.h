/*
 * ハードウェアの想定されている状態を定義する
 */

#ifndef HARDWARE_H
#define HARDWARE_H

// Configuration Bits
#include "ConfigurationBits.h"

// 電源電圧
#define POWER_SUPPLY_VOLTAGE	5.0

// 動作周波数
#define OPERATING_FREQUENCY	64000000L

// GPIO Port
#include "GPIOPort.h"
/**
 * GPIO PORTのオブジェクトを返す
 * @return GPIO Portの構造体ポインタ、取得できない場合はNULL
 */
GPIOPort* getPORTA(void);
GPIOPort* getPORTB(void);
GPIOPort* getPORTC(void);

// EUSART
#include "EUSART.h"
/**
 * EUSARTのオブジェクトを返す
 * @return EUSARTの構造体ポインタ，取得できない場合はNULL
 */
Eusart* getEUSART(void);	// alias of getEUSART1
Eusart* getEUSART1(void);
Eusart* getEUSART2(void);

// GPIO Pin
#include "GPIOPin.h"
/**
 * GPIOPinのオブジェクトを返す
 * @return GPIO Pinの構造体ポインタ，取得できない場合はNULL
 */
// PORTA
GPIOPin* getRA0(void);
GPIOPin* getRA1(void);
GPIOPin* getRA2(void);
GPIOPin* getRA3(void);
GPIOPin* getRA4(void);
GPIOPin* getRA5(void);
GPIOPin* getRA6(void);
GPIOPin* getRA7(void);
//PORTB
GPIOPin* getRB0(void);
GPIOPin* getRB1(void);
GPIOPin* getRB2(void);
GPIOPin* getRB3(void);
GPIOPin* getRB4(void);
GPIOPin* getRB5(void);
GPIOPin* getRB6(void);
GPIOPin* getRB7(void);
// PORTC
GPIOPin* getRC0(void);
GPIOPin* getRC1(void);
GPIOPin* getRC2(void);
GPIOPin* getRC3(void);
GPIOPin* getRC4(void);
GPIOPin* getRC5(void);
GPIOPin* getRC6(void);
GPIOPin* getRC7(void);
// PORTE is normaly used for MCLR, so GPIO functions are not supported

#endif /* HARDWARE_H */

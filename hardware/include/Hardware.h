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

// Oscillator Module
#include "OscillatorModule.h"
/**
 * Oscillator Moduleのオブジェクトを返す
 * @return Oscillator Moduleの構造体ポインタ，取得できない場合はNULL
 */
OscillatorModule* getOscillatorModule(void);
/**
 * Oscillator ModuleのselectSystemClockメソッドの引数に指定できる列挙型
 * hardware依存なのでOscillatorModule.hには書かず，ここで定義する
 */
typedef enum {
	INTERNAL,	// internal oscillator block
	SECONDARY,	// Secondary (SOSC) oscillator
	PRIMARY,	// Primary clock (determined by FOSC<3:0> in CONFIG1H) 
} OscillatorModule_clockSource;

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
/**
 * EUSARTの割り込みハンドラ
 * 割り込みを利用するときに割り込み中に呼び出すこと
 */
void EUSART1_handleInterrupt(void);
void EUSART2_handleInterrupt(void);

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

// Timer Module
#include "TimerModule.h"
/**
 * Timer Moduleのオブジェクトを返す
 * @return Timer Moduleの構造体ポインタ
 */
// 8 or 16 bit timer
TimerModule* getTimer0(void);
// 16 bit timer
TimerModule* getTimer1(void);
TimerModule* getTimer3(void);
TimerModule* getTimer5(void);
// 8 bit timer
TimerModule* getTimer2(void);
TimerModule* getTimer4(void);
TimerModule* getTimer6(void);
/**
 * Timer ModuleのselectClockSourceの引数に指定できる列挙型
 * タイマの種類によって異なるので注意
 */
typedef enum {
	CRYSTAL_OSCILLATOR,	// Crystal Oscillator on SOSCI/SOSCO pins
	EXTERNAL_CLOCK,		// External Clock from TxCKI pin (on the rising edge)
	SYSTEM_CLOCK,		// system clock (FOSC)
	INSTRUCTION_CLOCK,	// instruction clock (FOSC/4)
} TimerModule_clockSource;

#endif /* HARDWARE_H */

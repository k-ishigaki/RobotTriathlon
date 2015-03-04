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

/**
 * 割り込み優先度の定数
 * setInterruptPriorityメソッドに指定すること
 */
typedef enum {
	LOW_PRIORITY,
	HIGH_PRIORITY,
} Hardware_InterruptPriority;

// --------------------------------------------------------------------
// Oscillator Module
// --------------------------------------------------------------------
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

// --------------------------------------------------------------------
// GPIO Port
// --------------------------------------------------------------------
#include "GPIOPort.h"
/**
 * GPIO PORTのオブジェクトを返す
 * @return GPIO Portの構造体ポインタ、取得できない場合はNULL
 */
GPIOPort* getPORTA(void);
GPIOPort* getPORTB(void);
GPIOPort* getPORTC(void);

// --------------------------------------------------------------------
// EUSART
// --------------------------------------------------------------------
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

// --------------------------------------------------------------------
// GPIO Pin
// --------------------------------------------------------------------
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

// --------------------------------------------------------------------
// Timer Module
// --------------------------------------------------------------------
#include "TimerModule.h"

/**
 * Timer Moduleのオブジェクトを返す
 * @return Timer Moduleの構造体ポインタ
 */
// 8 or 16 bit timer
TimerModule* getTimer0(void);

/**
 * Timer1,3,5のインスタンス生成時に設定するクロック源の設定
 */
typedef enum {
	SIXTEEN_BIT_TIMER_CLOCKSOURCE_CRYSTAL_OSCILLATOR,	// Crystal Oscillator on SOSCI/SOSCO pins
	SIXTEEN_BIT_TIMER_CLOCKSOURCE_EXTERNAL_CLOCK,		// External Clock from TxCKI pin (on the rising edge)
	SIXTEEN_BIT_TIMER_CLOCKSOURCE_SYSTEM_CLOCK,		// system clock (FOSC)
	SIXTEEN_BIT_TIMER_CLOCKSOURCE_INSTRUCTION_CLOCK,	// instruction clock (FOSC/4)
} SixteenBitTimer_ClockSource;
/**
 * Timer1,3,5のインスタンス生成時に設定するプリスケーラの設定
 */
typedef enum {
	SIXTEEN_BIT_TIMER_PRISCALER_1_1,
	SIXTEEN_BIT_TIMER_PRISCALER_1_2,
	SIXTEEN_BIT_TIMER_PRISCALER_1_4,
	SIXTEEN_BIT_TIMER_PRISCALER_1_8,
} SixteenBitTimer_Prescaler;
/**
 * Timer1,3,5のコンストラクタ
 * @param クロックソースを表す列挙型定数
 * @param プリスケーラを表す列挙型定数
 */
TimerModule* getTimer1(SixteenBitTimer_ClockSource, SixteenBitTimer_Prescaler);
TimerModule* getTimer3(SixteenBitTimer_ClockSource, SixteenBitTimer_Prescaler);
TimerModule* getTimer5(SixteenBitTimer_ClockSource, SixteenBitTimer_Prescaler);
/**
 * Timer1,3,5の割り込みハンドラ
 */
void Timer1_handleInterrupt(void);
void Timer3_handleInterrupt(void);
void Timer5_handleInterrupt(void);

// 8 bit timer
/**
 * Timer2,4,6の生成に必要なプリスケーラの値．
 */
typedef enum {
	EIGHT_BIT_TIMER_PRISCALER_1_1,
	EIGHT_BIT_TIMER_PRISCALER_1_4,
	EIGHT_BIT_TIMER_PRISCALER_1_16,
} EightBitTimer_Priscaler;
/**
 * Timer2,4,6の生成に必要なポストスケーラの値．
 */
typedef enum {
	EIGHT_BIT_TIMER_POSTSCALER_1_1,
	EIGHT_BIT_TIMER_POSTSCALER_1_2,
	EIGHT_BIT_TIMER_POSTSCALER_1_3,
	EIGHT_BIT_TIMER_POSTSCALER_1_4,
	EIGHT_BIT_TIMER_POSTSCALER_1_5,
	EIGHT_BIT_TIMER_POSTSCALER_1_6,
	EIGHT_BIT_TIMER_POSTSCALER_1_7,
	EIGHT_BIT_TIMER_POSTSCALER_1_8,
	EIGHT_BIT_TIMER_POSTSCALER_1_9,
	EIGHT_BIT_TIMER_POSTSCALER_1_10,
	EIGHT_BIT_TIMER_POSTSCALER_1_11,
	EIGHT_BIT_TIMER_POSTSCALER_1_12,
	EIGHT_BIT_TIMER_POSTSCALER_1_13,
	EIGHT_BIT_TIMER_POSTSCALER_1_14,
	EIGHT_BIT_TIMER_POSTSCALER_1_15,
	EIGHT_BIT_TIMER_POSTSCALER_1_16,
} EightBitTimer_Postscaler;
/**
 * 8ビットタイマのコンストラクタ．
 * @param プリスケーラ値
 * @param ポストスケーラ値
 */
TimerModule* getTimer2(EightBitTimer_Priscaler, EightBitTimer_Postscaler);
TimerModule* getTimer4(EightBitTimer_Priscaler, EightBitTimer_Postscaler);
TimerModule* getTimer6(EightBitTimer_Priscaler, EightBitTimer_Postscaler);
/**
 * Timer2,4,6の割り込みハンドラ
 */
void Timer2_handleInterrupt(void);
void Timer4_handleInterrupt(void);
void Timer6_handleInterrupt(void);

// --------------------------------------------------------------------
// ECCP Module
// --------------------------------------------------------------------
#include "ECCPModule.h"

/**
 * ECCP Moduleのタイマソース
 * Timer1,3,5から選択可能
 */
typedef enum {
	ECCP_MODULE_TIMR_SOURCE_TIMER1_TIMER2,
	ECCP_MODULE_TIMR_SOURCE_TIMER3_TIMER4,
	ECCP_MODULE_TIMR_SOURCE_TIMER5_TIMER6,
} ECCPModule_TimerSource;

/**
 * EnhancedPWMDriverの動作モード
 */
typedef enum {
	ENHANCED_PWM_DRIVER_MODE_SINGLE,
	ENHANCED_PWM_DRIVER_MODE_HALF_BRIDGE,
	ENHANCED_PWM_DRIVER_MODE_FULL_BRIDGE,
} EnhancedPWMDriver_Mode;

/**
 * EnhancedPWMDriverの出力モード．
 */
typedef enum {
	ENHANCED_PWM_DRIVER_OUTPUT_MODE_ACTIVE_HIGH_ACTIVE_HIGH,
	ENHANCED_PWM_DRIVER_OUTPUT_MODE_ACTIVE_HIGH_ACTIVE_LOW,
	ENHANCED_PWM_DRIVER_OUTPUT_MODE_ACTIVE_LOW_ACTIVE_HIGH,
	ENHANCED_PWM_DRIVER_OUTPUT_MODE_ACTIVE_LOW_ACTIVE_LOW,
} EnhancedPWMDriver_OutputMode;

/**
 * ECCP Moduleのオブジェクトを返す．
 * @return ECCPModuleの構造体ポインタ
 */
// Enhanced CCP
ECCPModule* getECCP1(ECCPModule_TimerSource);
ECCPModule* getECCP2(ECCPModule_TimerSource);
ECCPModule* getECCP3(ECCPModule_TimerSource);
// Standard CCP
ECCPModule* getCCP4(ECCPModule_TimerSource);
ECCPModule* getCCP5(ECCPModule_TimerSource);

/**
 * ECCP，CCPの割り込みハンドラ
 */
void ECCP1_handleInterrupt(void);
void ECCP2_handleInterrupt(void);
void ECCP3_handleInterrupt(void);
void CCP4_handleInterrupt(void);
void CCP5_handleInterrupt(void);

// --------------------------------------------------------------------
// Comparator Module
// --------------------------------------------------------------------
#include "ComparatorModule.h"

/**
 * Comparator Moduleのリファレンス．
 */
typedef enum {
	COMPARATOR_MODULE_REFERENCE_DAC,
	COMPARATOR_MODULE_REFERENCE_FVR_BUF1,
} ComparatorModule_Reference;
/**
 * Comparator Moduleのヒステリシス有効化．
 */
typedef enum {
	COMPARATOR_MODULE_HYSTERESIS_DISABLE,
	COMPARATOR_MODULE_HYSTERESIS_ENABLE,
} ComparatorModule_Hysteresis;
/**
 * Comparator Moduleの同期モード．
 */
typedef enum {
	COMPARATOR_MODULE_SYNCHRONOUS_MODE_ASYNCHRONOUS,
	COMPARATOR_MODULE_SYNCHRONOUS_MODE_T1CLK,
} ComparatorModule_SynchronousMode;
/**
 * コンパレータのチャンネル．
 */
typedef enum {
	COMPARATOR_MODULE_CHANNEL_C12IN0,
	COMPARATOR_MODULE_CHANNEL_C12IN1,
	COMPARATOR_MODULE_CHANNEL_C12IN2,
	COMPARATOR_MODULE_CHANNEL_C12IN3,
} ComparatorModule_Channel;

/**
 * Comparator Moduleのオブジェクトを返す．
 * @return ComparatorModuleの構造体ポインタ
 */
ComparatorModule* getComparator1(
		ComparatorModule_Reference,
		ComparatorModule_Hysteresis,
		ComparatorModule_SynchronousMode);
ComparatorModule* getComparator2(
		ComparatorModule_Reference,
		ComparatorModule_Hysteresis,
		ComparatorModule_SynchronousMode);
/**
 * Comparator Moduleの割り込みハンドラ．
 */
void Comparator1_handleInterrupt(void);
void Comparator2_handleInterrupt(void);

// --------------------------------------------------------------------
// MSSP Module
// --------------------------------------------------------------------
#include "MSSPModule.h"
/**
 * MSSP Moduleのオブジェクトを返す．
 * @return MSSPModuleの構造体ポインタ
 */
MSSPModule* getMSSP1(DigitalPin*, DigitalPin*);
MSSPModule* getMSSP2(DigitalPin*, DigitalPin*);

#endif /* HARDWARE_H */

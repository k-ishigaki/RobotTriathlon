/*
 * PICのGPIO Portを操作するオブジェクトのインターフェース定義
 * 最低限持っているであろう機能を提供する
 */

#ifndef GPIO_PORT_H
#define GPIO_PORT_H

typedef void (*GPIOPort_setAnalogInput)(unsigned char pattern);
typedef void (*GPIOPort_setAnalogOutput)(unsigned char pattern);
typedef void (*GPIOPort_setDigitalInput)(unsigned char pattern);
typedef void (*GPIOPort_setDigitalOutput)(unsigned char pattern);
typedef unsigned char (*GPIOPort_getValue)(void);
typedef void (*GPIOPort_setValue)(unsigned char pattern);

// GPIO PORTのオブジェクト
// PORTx.cで実体を定義
typedef struct {
	/**
	 * 指定したビットに対応するポートのピンをアナログ入力に設定する
	 * @param pattern 1にした部分のみを設定する
	 */
	GPIOPort_setAnalogInput setAnalogInput;
	/**
	 * 指定したビットに対応するポートのピンをアナログ出力に設定する
	 * @param pattern 1にした部分のみを設定する
	 */
	GPIOPort_setAnalogOutput setAnalogOutput;
	/**
	 * 指定したビットに対応するポートのピンをデジタル入力に設定する
	 * @param pattern 1にした部分のみを設定する
	 */
	GPIOPort_setDigitalInput setDigitalInput;
	/**
	 * 指定したビットに対応するポートのピンをデジタル出力に設定する
	 * @param pattern 1にした部分のみを設定する
	 */
	GPIOPort_setDigitalOutput setDigitalOutput;
	/**
	 * ポートの入力状態を返す
	 * @return PORTxの内容をそのまま返す
	 */
	GPIOPort_getValue getValue;
	/**
	 * ポートの出力を設定する
	 * @param pattern 1の部分をHIGH、0の部分をLOWに設定する
	 */
	GPIOPort_setValue setValue;
} GPIOPort;

GPIOPort* getPORTA(void);

#endif /* GPIO_PORT_H */

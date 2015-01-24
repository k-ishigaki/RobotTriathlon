/*
 * PICのGPIO Portを操作するオブジェクトのインターフェース定義
 * 最低限持っているであろう機能を提供する
 */

#ifndef GPIO_PORT_H
#define GPIO_PORT_H

typedef void (*GPIOPort_setAnalogInput)(char pattern);
typedef void (*GPIOPort_setAnalogOutput)(char pattern);
typedef void (*GPIOPort_setDigitalInput)(char pattern);
typedef void (*GPIOPort_setDigitalOutput)(char pattern);
typedef void (*GPIOPort_getValue)(char patten);
typedef void (*GPIOPort_setValue)(char patten);

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
} GPIOPort;

#endif /* GPIO_PORT_H */

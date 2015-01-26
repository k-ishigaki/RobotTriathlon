/*
 * PICのGPIO Portを操作するオブジェクトのインターフェース定義
 * 最低限持っているであろう機能を提供する
 */

#ifndef GPIO_PORT_H
#define GPIO_PORT_H

typedef void (*GPIOPort_setAnalogInputInterface)(unsigned char pattern);
typedef void (*GPIOPort_setAnalogOutputInterface)(unsigned char pattern);
typedef void (*GPIOPort_setDigitalInputInterface)(unsigned char pattern);
typedef void (*GPIOPort_setDigitalOutputInterface)(unsigned char pattern);
typedef unsigned char (*GPIOPort_getValueInterface)(void);
typedef void (*GPIOPort_setValueInterface)(unsigned char pattern);

// GPIO PORTのオブジェクト
// PORTx.cで実体を定義
typedef struct {
	/**
	 * 指定したビットに対応するポートのピンをアナログ入力に設定する
	 * @param pattern 1にした部分のみを設定する
	 */
	GPIOPort_setAnalogInputInterface setAnalogInput;
	/**
	 * 指定したビットに対応するポートのピンをアナログ出力に設定する
	 * @param pattern 1にした部分のみを設定する
	 */
	GPIOPort_setAnalogOutputInterface setAnalogOutput;
	/**
	 * 指定したビットに対応するポートのピンをデジタル入力に設定する
	 * @param pattern 1にした部分のみを設定する
	 */
	GPIOPort_setDigitalInputInterface setDigitalInput;
	/**
	 * 指定したビットに対応するポートのピンをデジタル出力に設定する
	 * @param pattern 1にした部分のみを設定する
	 */
	GPIOPort_setDigitalOutputInterface setDigitalOutput;
	/**
	 * ポートの入力状態を返す
	 * @return PORTxの内容をそのまま返す
	 */
	GPIOPort_getValueInterface getValue;
	/**
	 * ポートの出力を設定する
	 * @param pattern 1の部分をHIGH、0の部分をLOWに設定する
	 */
	GPIOPort_setValueInterface setValue;
} GPIOPort;

#endif /* GPIO_PORT_H */

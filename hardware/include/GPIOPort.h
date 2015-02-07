/*
 * PICのGPIO Portを操作するオブジェクトのインターフェース定義
 * 最低限持っているであろう機能を提供する
 */

#ifndef GPIO_PORT_H
#define GPIO_PORT_H

#include <stdint.h>

// GPIO PORTのオブジェクト
// PORTx.cで実体を定義
typedef struct {
	/**
	 * 指定したビットに対応するポートのピンをアナログ入力に設定する
	 * @param pattern 1にした部分のみを設定する
	 */
	void (*setAnalogInput)(uint8_t pattern);
	/**
	 * 指定したビットに対応するポートのピンをアナログ出力に設定する
	 * @param pattern 1にした部分のみを設定する
	 */
	void (*setAnalogOutput)(uint8_t pattern);
	/**
	 * 指定したビットに対応するポートのピンをデジタル入力に設定する
	 * @param pattern 1にした部分のみを設定する
	 */
	void (*setDigitalInput)(uint8_t pattern);
	/**
	 * 指定したビットに対応するポートのピンをデジタル出力に設定する
	 * @param pattern 1にした部分のみを設定する
	 */
	void (*setDigitalOutput)(uint8_t pattern);
	/**
	 * ポートの入力状態を返す
	 * @return PORTxの内容をそのまま返す
	 */
	uint8_t (*getValue)(void);
	/**
	 * ポートの出力を設定する
	 * @param pattern 1の部分をHIGH、0の部分をLOWに設定する
	 */
	void (*setValue)(uint8_t pattern);
} GPIOPort;

#endif /* GPIO_PORT_H */

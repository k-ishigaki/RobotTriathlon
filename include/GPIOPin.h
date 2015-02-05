/*
 * GPIOピンのインターフェース
 * デジタルピンとアナログピンのインターフェースを持つ
 */
#ifndef GPIO_PIN_H
#define GPIO_PIN_H

#include <stdbool.h>

typedef struct {
	/**
	 * デジタル入力に設定する
	 */
	void (*setDigitalInput)(void);
	/**
	 * デジタル出力に設定する
	 */
	void (*setDigitalOutput)(void);
	/**
	 * ピンの状態を取得する
	 * @return PORTの値、LOWならfalse、HIGHならtrue
	 */
	bool (*getValue)(void);
	/**
	 * ピンの出力を設定する
	 * @param falseならLOW、trueならHIGHを設定
	 */
	void (*setValue)(bool state);
} DigitalPin;

typedef struct {
	/**
	 * アナログ入力に設定する
	 */
	void (*setAnalogInput)(void);
	/**
	 * アナログ出力に設定する
	 */
	void (*setAnalogOutput)(void);
} AnalogPin;

typedef struct {
	/**
	 * デジタルピンのインターフェースを取得
	 * @return DigitalPinインターフェース
	 */
	DigitalPin* (*getDigitalPin)(void);
	/**
	 * アナログピンのインターフェースを取得
	 * @return AnalogPinインターフェース、持っていない場合はNULL
	 */
	AnalogPin* (*getAnalogPin)(void);
} GPIOPin;

#endif /* GPIO_PIN_H */

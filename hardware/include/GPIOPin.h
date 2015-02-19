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
	 * 内部プルアップを有効にする
	 * 有効にするためにはINTCONxでポートごとの内部プルアップを有効にする必要がある
	 */
	void (*enableInternalPullup)(void);
	/**
	 * 内部プルアップを無効にする
	 */
	void (*disableInternalPullup)(void);
	/**
	 * ピンの状態を取得する
	 * 出力に設定されているときは出力状態を，
	 * 入力に設定されているときは入力状態を返す
	 * @return LOWならfalse、HIGHならtrue
	 */
	bool (*getValue)(void);
	/**
	 * ピンの出力を設定する
	 * @param state falseならLOW、trueならHIGHを設定
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

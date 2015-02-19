/*
 * GPIOピンのインターフェース
 * デジタルピンとアナログピンのインターフェースを持つ
 */
#ifndef GPIO_PIN_H
#define GPIO_PIN_H

#include <stdbool.h>

typedef struct {
	/**
	 * ピンの状態を取得する
	 * @return HIGHならtrue，LOWならfalse
	 */
	bool (*getValue)(void);
} DigitalPullupedInputPin;

typedef struct {
	/**
	 * ピンの状態を取得する
	 * @return HIGHならtrue，LOWならfalse
	 */
	bool (*getValue)(void);
	/**
	 * プルアップ入力ピンを取得する
	 * @return DigitalPullupedInputPinのインターフェース
	 */
	DigitalPullupedInputPin* (*getPullupedPin)(void);
} DigitalInputPin;

typedef struct {
	/**
	 * 出力状態を取得する
	 * @return HIGHならtrue，LOWならfalse
	 */
	bool (*getValue)(void);
	/**
	 * 出力状態を設定する
	 * @param trueならHIGH，falseならLOWを設定
	 */
	void (*setValue)(bool);
} DigitalOutputPin;

typedef struct {
	/**
	 * 入出力の方向を設定する
	 * @param 方向，trueで出力，falseで入力
	 */
	void (*setDirection)(bool);
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
	 * 入出力方向を設定する
	 * DAC出力を行うときに一応呼び出すこと（ほとんどの場合は呼ぶ必要はないが）
	 * @param 方向，trueで出力，falseで入力
	 */
	void (*setDirection)(bool);
} AnalogPin;

typedef struct {
	/**
	 * デジタル入力ピンを取得
	 * @return DigitalInputPinインターフェース
	 */
	DigitalInputPin* (*getDigitalInputPin)(void);
	/**
	 * デジタル出力ピンを取得
	 * @return DigitalOutputPinインターフェース，持っていない場合はNULL
	 */
	DigitalOutputPin* (*getDigitalOutputPin)(void);
	/**
	 * デジタルピン（入出力可能ピン）を取得
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

/*
 * GPIOピンのインターフェース
 * デジタルピンとアナログピンのインターフェースを持つ
 */
#ifndef GPIO_PIN_H
#define GPIO_PIN_H

typedef void (*DigitalPin_setDigitalInput)();
typedef void (*DigitalPin_setDigitalOutput)();
typedef unsigned char (*DigitalPin_getValue)(void);
typedef void (*DigitalPin_setValue)(unsigned char value);

typedef void (*AnalogPin_setAnalogInput)();
typedef void (*AnalogPin_setAnalogOutput)();

typedef struct {
	/**
	 * デジタル入力に設定する
	 */
	DigitalPin_setDigitalInput setDigitalInput;
	/**
	 * デジタル出力に設定する
	 */
	DigitalPin_setDigitalOutput setDigitalOutput;
	/**
	 * ピンの状態を取得する
	 * @return PORTの値、LOWなら0、HIGHなら1
	 */
	DigitalPin_getValue getValue;
	/**
	 * ピンの出力を設定する
	 * @param 0ならLOW、1ならHIGHを設定
	 */
	DigitalPin_setValue setValue;
} DigitalPin;

typedef struct {
	/**
	 * アナログ入力に設定する
	 */
	AnalogPin_setAnalogInput setAnalogInput;
	/**
	 * アナログ出力に設定する
	 */
	AnalogPin_setAnalogOutput setAnalogOutput;
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

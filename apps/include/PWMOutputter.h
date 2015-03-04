/*
 * PWMのオン，オフを切り替えられるインターフェース
 */
#ifndef PWM_OUTPUTTER_H
#define PWM_OUTPUTTER_H

#include "Hardware.h"

typedef struct {
	/**
	 * PWMの出力を有効にする．
	 */
	void (*enablePWMOutput)(void);
	/**
	 * PWMの出力を無効にする．
	 */
	void (*disablePWMOutput)(void);
} PWMOutputter;

/**
 * PWMOutputterのコンストラクタ．
 * 割り込みは一切利用しない．
 * EnhancedPWMDriverのタイマソースは外部で有効にする必要がある．
 */
PWMOutputter* getPWMOutputter1(
		DigitalPin*,
		DigitalPin*,
		EnhancedPWMDriver*);

PWMOutputter* getPWMOutputter2(
		DigitalPin*,
		DigitalPin*,
		EnhancedPWMDriver*);


#endif /* PWM_OUTPUTTER_H */

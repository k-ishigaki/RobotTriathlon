#ifndef SPEED_COUNTER_H
#define SPEED_COUNTER_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	/**
	 * カウント取得周期で呼び出される．
	 * @param ある周期で取得したカウント（~スピード）
	 */
	void (*onSpeedChanged)(uint8_t);
} SpeedCountListener;

typedef struct {
	/**
	 * 現時点でのスピードを取得する．
	 * @return スピード（〜カウント数）
	 */
	uint8_t (*getSpeedCount)(void);
	/**
	 * スピード変化監視リスナを登録する．
	 * @param スピード変化監視リスナ
	 */
	void (*addSpeedCountListener)(SpeedCountListener*);
} SpeedCounter;

/**
 * スピードカウンタのコンストラクタ
 * @param コンパレータモジュール
 * @param 周期的割り込みコントローラ
 */
SpeedCounter* getLeftSpeedCounter(ComparatorModule*, PeriodicInterruptController*);
SpeedCounter* getRightSpeedCounter(ComparatorModule*, PeriodicInterruptController*);

#endif /* SPEED_COUNTER_H */

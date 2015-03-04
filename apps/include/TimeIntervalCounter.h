#ifndef TIME_INTERVAL_COUNTER_H
#define TIME_INTERVAL_COUNTER_H

#include "Hardware.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	/**
	 * タイマを0からスタートさせる．
	 */
	void (*startTimer)(void);
	/**
	 * キャプチャを開始して，1回のみキャプチャする．
	 */
	void (*startCapturing)(void);
	/**
	 * キャプチャした値を返す．
	 * キャプチャしていない場合は0を返す．
	 */
	uint16_t (*getCapturedValue)(void);
} TimeIntervalCounter;

/**
 * 時間間隔カウンタのインターフェースを取得する．
 * @param カウント元のタイマモジュール
 * @param インプットキャプチャに使うデジタルピン
 * @param 第一引数のタイマをソースにしたインプットキャプチャ
 */
TimeIntervalCounter* getTimeIntervalCounter1(
		TimerModule*,
		DigitalPin*,
		InputCaptureController*);

TimeIntervalCounter* getTimeIntervalCounter2(
		TimerModule*,
		DigitalPin*,
		InputCaptureController*);

#endif /* TIME_INTERVAL_COUNTER_H */

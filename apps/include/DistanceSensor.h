/*
 * 距離センサを扱う．
 * タイマとインプットキャプチャ，タスクマネージャを扱う．
 */
#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H

#include "Hardware.h"
#include "PWMOutputter.h"
#include "TaskManager.h"
#include "TimeIntervalCounter.h"

typedef struct {
	/**
	 * センサの距離を取得する．
	 * @return 距離（タイマのカウント基準）
	 */
	uint16_t (*getDistaneCount)(void);
} DistanceSensor;

/**
 * 距離センサのコンストラクタ．
 * @param PWM出力インターフェース
 * @param 時間間隔測定のインターフェース
 * @param タスクマネージャのインターフェース
 */
DistanceSensor* getDistanceSensor1(
		PWMOutputter*,
		TimeIntervalCounter*,
		TaskManager*);

DistanceSensor* getDistanceSensor2(
		PWMOutputter*,
		TimeIntervalCounter*,
		TaskManager*);


#endif /* DISTANCE_SENSOR_H */

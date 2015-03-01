/*
 * マシンの動作を設定するインターフェース．
 * LineTracer，ObstacleDodgerで共通に利用される．
 * SpeedCounter，MotorDriverが必要．
 */
#ifndef MOTION_CONTROLLER_H
#define MOTION_CONTROLLER_H

#include "MotorDriver.h"
#include "GPIOPort.h"
#include "TimerModule.h"
#include "ECCPModule.h"

typedef struct {
	/**
	 * 停止する．
	 * 急には止まれない．
	 * 目標距離で止まらせたいときは，moveDistanceを使うこと．
	 */
	void stop(void);
	/**
	 * 一定速度で前進しようとする．
	 * 引数に負の値を指定すると，後ろに直進する．
	 * @param SpeedCounterが計測するカウント数が基準の速度
	 */
	void moveStraight(int);
	/**
	 * 指定した速度，曲率で移動しようとする．
	 * 第一引数に負の値を指定すると，後ろに移動する．
	 * 超信地回転はできない．
	 * あまりきつい曲率は指定しないこと．
	 * @param 速度（カウント基準）
	 * @param 曲率半径（cm単位で指定，正で左回り，負で右回り）
	 */
	void moveCorner(int, int);
	/**
	 * 一定速度で一定距離進んだ後，停止する．
	 * 第一引数に負の値を指定すると，後ろに直進する．
	 * 第二引数に停止するまでの目標距離を，カウント単位で指定する．
	 * @param SpeedCounterが計測するカウント数が基準の速度
	 * @param 目標積算カウント数
	 */
	void moveDistance(int, unsigned long);
} MotionController;

/**
 * マシンの移動インターフェースを取得する
 * @param MotorDriverのインターフェース
 * @param SpeedCounterのインターフェース
 */
MotionController* getMotionController(MotorDriver*, SpeedCounter*);

#endif

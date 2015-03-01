#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "Hardware.h"

#include <stdint.h>

typedef struct {
	/**
	 * フリー回転させる
	 */
	void (*setFree)(void);
	/**
	 * 順回転させる．
	 */
	void (*setForward)(void);
	/**
	 * 逆回転させる
	 */
	void (*setBackward)(void);
	/**
	 * ストップさせる
	 */
	void (*setStop)(void);
	/**
	 * PWMのデューティー比を設定する
	 * デューティー比を0~1023までの整数で指定すること
	 * @param デューティー比
	 */
	void (*setPWMDutyValue)(uint16_t);
} MotorDriver;

/**
 * モータドライバのオブジェクトを取得する
 * @param 周期的割り込みコントローラ
 * @param コンペアマッチ割り込みコントローラ
 * @param 汎用入出力ポート
 * @param 利用するピン
 * @param freeの時のパターン
 * @param forward時のパターン
 * @param backward時のパターン
 * @param stop時のパターン
 */
MotorDriver* getLeftMotor(
		PeriodicInterruptController*,
		CompareMatchInterruptController*,
		GPIOPort*,
		uint8_t,
		uint8_t,
		uint8_t,
		uint8_t,
		uint8_t);
MotorDriver* getRightMotor(
		PeriodicInterruptController*,
		CompareMatchInterruptController*,
		GPIOPort*,
		uint8_t,
		uint8_t,
		uint8_t,
		uint8_t,
		uint8_t);

#endif /* MOTOR_DRIVER_H */

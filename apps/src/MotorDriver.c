/**
 * MotorDriverの実体定義．
 * LeftMotorDriver, RightMotorDriverの実装を記述する．
 * このファイルには名前空間定義を，substance.cファイルで
 * 実装をまとめて記述している．
 */
#include "MotorDriver.h"

#define USING_MOTOR_DRIVER_SUBSTANCE

#define NAMESPACE(name) LeftMotor_##name
#define LeftMotor_getter getLeftMotor
#include "MotorDriver.substance.c"

#define NAMESPACE(name) RightMotor_##name
#define RightMotor_getter getRightMotor
#include "MotorDriver.substance.c"

#include "Hardware.h"
#include "SpeedCounter.h"

#define USING_SPEED_COUNTER_SUBSTANCE

#define LeftSpeedCounter_getter getLeftSpeedCounter
#define NAMESPACE(name) LeftSpeedCounter_##name
#include "SpeedCounter.substance.c"

#define RightSpeedCounter_getter getRightSpeedCounter
#define NAMESPACE(name) RightSpeedCounter_##name
#include "SpeedCounter.substance.c"


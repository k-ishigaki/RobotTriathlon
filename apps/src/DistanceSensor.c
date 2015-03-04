#include "DistanceSensor.h"

#define USING_DISTANCE_SENSOR_SUBSTANCE

#define NAMESPACE(name) DistanceSensor1_##name
#define DistanceSensor1_getter getDistanceSensor1
#include "DistanceSensor.substance.c"

#define NAMESPACE(name) DistanceSensor2_##name
#define DistanceSensor2_getter getDistanceSensor2
#include "DistanceSensor.substance.c"

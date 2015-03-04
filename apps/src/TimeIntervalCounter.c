#include "TimeIntervalCounter.h"

#define USING_TIME_INTERVAL_COUNTER_SUBSTANCE

#define NAMESPACE(name) TimeIntervalCounter1_##name
#define TimeIntervalCounter1_getter getTimeIntervalCounter1
#include "TimeIntervalCounter.substance.c"

#define NAMESPACE(name) TimeIntervalCounter2_##name
#define TimeIntervalCounter2_getter getTimeIntervalCounter2
#include "TimeIntervalCounter.substance.c"


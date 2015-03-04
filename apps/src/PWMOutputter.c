#include "PWMOutputter.h"

#define USING_PWM_OUTPUTTER_SUBSTANCE

#define NAMESPACE(name) PWMOutputter1_##name
#define PWMOutputter1_getter getPWMOutputter1

#include "PWMOutputter.substance.c"

#define NAMESPACE(name) PWMOutputter2_##name
#define PWMOutputter2_getter getPWMOutputter2
#include "PWMOutputter.substance.c"

#include "ComparatorModule.h"
#include "Hardware.h"

#define USING_COMPARATOR_MODULE_SUBSTANCE


// registers
#define Comparator1_CMxCON0 CM1CON0bits
#define Comparator1_CMxCON1 CM2CON1bits
#define Comparator1_IPRx IPR2bits
#define Comparator1_PIEx PIE2bits
#define Comparator1_PIRx PIR2bits
// string concatenation
#define NAMESPACE(name) Comparator1_##name
#define Cx(name) C1##name
#define MCx(name) MC1##name
// getter
#define Comparator1_getter getComparator1

#include "ComparatorModule.substance.c"

// registers
#define Comparator2_CMxCON0 CM2CON0bits
#define Comparator2_CMxCON1 CM2CON1bits
#define Comparator2_IPRx IPR2bits
#define Comparator2_PIEx PIE2bits
#define Comparator2_PIRx PIR2bits
// string concatenation
#define NAMESPACE(name) Comparator2_##name
#define Cx(name) C2##name
#define MCx(name) MC2##name
// getter
#define Comparator2_getter getComparator2

#include "ComparatorModule.substance.c"


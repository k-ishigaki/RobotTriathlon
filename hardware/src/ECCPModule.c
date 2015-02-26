/**
 * ECCP Moduleの実体定義．
 * ECCP1,2,3,4,5の実装を記述する．
 * このファイルにはレジスタ定義などを，substance.cファイルで
 * 定義ごとに分岐して実装を記述している．
 */

#include "Hardware.h"

#define USING_ECCP_MODULE_SUBSTANCE

// ECCP1
// include substance.c as a Enhanced CCP Module
#define IS_ECCP
// register
#define ECCP1_CCPxCON CCP1CONbits
#define ECCP1_CCPRxH CCPR1Hbits
#define ECCP1_CCPRxL CCPR1Lbits
#define ECCP1_CCPTMRSx CCPTMRS0bits
#define ECCP1_IPRx IPR1bits
#define ECCP1_PIEx PIE1bits
#define ECCP1_PIRx PIR1bits
// string concatenation
#define NAMESPACE(name) ECCP1_##name
#define CCPx(name) CCP1##name
#define Cx(name) C1##name
#define CCPRx(name) CCPR1##name
// getter function name
#define ECCP1_getter getECCP1
#include "ECCPModule.substance.c"



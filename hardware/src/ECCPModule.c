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
#define DCx(name) DC1##name
#define Px(name) P1##name
// getter function name
#define ECCP1_getter getECCP1
#include "ECCPModule.substance.c"

// ECCP2
// include substance.c as a Enhanced CCP Module
#define IS_ECCP
// register
#define ECCP2_CCPxCON CCP2CONbits
#define ECCP2_CCPRxH CCPR2Hbits
#define ECCP2_CCPRxL CCPR2Lbits
#define ECCP2_CCPTMRSx CCPTMRS0bits
#define ECCP2_IPRx IPR2bits
#define ECCP2_PIEx PIE2bits
#define ECCP2_PIRx PIR2bits
// string concatenation
#define NAMESPACE(name) ECCP2_##name
#define CCPx(name) CCP2##name
#define Cx(name) C2##name
#define CCPRx(name) CCPR2##name
#define DCx(name) DC2##name
#define Px(name) P2##name
// getter function name
#define ECCP2_getter getECCP2
#include "ECCPModule.substance.c"

// ECCP3
// include substance.c as a Enhanced CCP Module
#define IS_ECCP
// register
#define ECCP3_CCPxCON CCP3CONbits
#define ECCP3_CCPRxH CCPR3Hbits
#define ECCP3_CCPRxL CCPR3Lbits
#define ECCP3_CCPTMRSx CCPTMRS0bits
#define ECCP3_IPRx IPR4bits
#define ECCP3_PIEx PIE4bits
#define ECCP3_PIRx PIR4bits
// string concatenation
#define NAMESPACE(name) ECCP3_##name
#define CCPx(name) CCP3##name
#define Cx(name) C3##name
#define CCPRx(name) CCPR3##name
#define DCx(name) DC3##name
#define Px(name) P3##name
// getter function name
#define ECCP3_getter getECCP3
#include "ECCPModule.substance.c"

// CCP4
// include substance.c as a Standard CCP Module
#define IS_CCP
// register
#define CCP4_CCPxCON CCP4CONbits
#define CCP4_CCPRxH CCPR4Hbits
#define CCP4_CCPRxL CCPR4Lbits
#define CCP4_CCPTMRSx CCPTMRS1bits
#define CCP4_IPRx IPR4bits
#define CCP4_PIEx PIE4bits
#define CCP4_PIRx PIR4bits
// string concatenation
#define NAMESPACE(name) CCP4_##name
#define CCPx(name) CCP4##name
#define Cx(name) C4##name
#define CCPRx(name) CCPR4##name
#define DCx(name) DC4##name
#define Px(name) P4##name
// getter function name
#define CCP4_getter getCCP4
#include "ECCPModule.substance.c"

// CCP5
// include substance.c as a Standard CCP Module
#define IS_CCP
// register
#define CCP5_CCPxCON CCP5CONbits
#define CCP5_CCPRxH CCPR5Hbits
#define CCP5_CCPRxL CCPR5Lbits
#define CCP5_CCPTMRSx CCPTMRS1bits
#define CCP5_IPRx IPR4bits
#define CCP5_PIEx PIE4bits
#define CCP5_PIRx PIR4bits
// string concatenation
#define NAMESPACE(name) CCP5_##name
#define CCPx(name) CCP5##name
#define Cx(name) C5##name
#define CCPRx(name) CCPR5##name
#define DCx(name) DC5##name
#define Px(name) P5##name
// getter function name
#define CCP5_getter getCCP5
#include "ECCPModule.substance.c"


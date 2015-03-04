#include "MSSPModule.h"
#include "Hardware.h"

#define USING_MSSP_MODULE_SUBSTANCE

// registers
#define MSSP1_SSPxADD SSP1ADDbits
#define MSSP1_SSPxBUF SSP1BUFbits
#define MSSP1_SSPxCON1 SSP1CON1bits
#define MSSP1_SSPxCON2 SSP1CON2bits
#define MSSP1_SSPxCON3 SSP1CON3bits
#define MSSP1_SSPxMSK SSP1MSKbits
#define MSSP1_SSPxSTAT SSP1STATbits
#define MSSP1_PIRx PIR1bits
#define MSSP1_getter getMSSP1
// string concatenation
#define NAMESPACE(name) MSSP1_##name
#define SSPx(name) SSP1##name
#include "MSSPModule.substance.c"

// registers
//#define MSSP2_SSPxADD SSP2ADDbits
//#define MSSP2_SSPxBUF SSP2BUFbits
//#define MSSP2_SSPxCON1 SSP2CON1bits
//#define MSSP2_SSPxCON2 SSP2CON2bits
//#define MSSP2_SSPxCON3 SSP2CON3bits
//#define MSSP2_SSPxMSK SSP2MSKbits
//#define MSSP2_SSPxSTAT SSP2STATbits
//#define MSSP2_PIRx PIR3bits
//#define MSSP2_getter getMSSP2
//// string concatenation
//#define NAMESPACE(name) MSSP2_##name
//#define SSPx(name) SSP2##name
//#include "MSSPModule.substance.c"


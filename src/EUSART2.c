#include <xc.h>
#include "Hardware.h"
#include "EUSART.h"
// EUSARTの実体を利用する
#define USING_EUSART_SUBSTANCE
#define NAMESPACE(name) EUSART2_##name

RCSTAbits_t* NAMESPACE(rcsta) = (RCSTAbits_t*)&RCSTA2bits;
TXSTAbits_t* NAMESPACE(txsta) = (TXSTAbits_t*)&TXSTA2bits;
BAUDCONbits_t* NAMESPACE(baudcon) = (BAUDCONbits_t*)&BAUDCON2bits;
SPBRGbits_t* NAMESPACE(spbrg) = (SPBRGbits_t*)&SPBRG2bits;
RCREGbits_t* NAMESPACE(rcreg) = (RCREGbits_t*)&RCREG2bits;
TXREGbits_t* NAMESPACE(txreg) = (TXREGbits_t*)&TXREG2bits;

#include "EUSART.substance.c"

Eusart* getEUSART2() {
	return (Eusart*)&NAMESPACE(eusart);
}

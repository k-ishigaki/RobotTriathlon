#include <xc.h>
#include "Hardware.h"
#include "EUSART.h"
// EUSARTの実体を利用する
#define USING_EUSART_SUBSTANCE
#define NAMESPACE(name) EUSART_##name

RCSTAbits_t* NAMESPACE(rcsta) = (RCSTAbits_t*)&RCSTAbits;
TXSTAbits_t* NAMESPACE(txsta) = (TXSTAbits_t*)&TXSTAbits;
BAUDCONbits_t* NAMESPACE(baudcon) = (BAUDCONbits_t*)&BAUDCONbits;
SPBRGbits_t* NAMESPACE(spbrg) = (SPBRGbits_t*)&SPBRGbits;
RCREGbits_t* NAMESPACE(rcreg) = (RCREGbits_t*)&RCREGbits;
TXREGbits_t* NAMESPACE(txreg) = (TXREGbits_t*)&TXREGbits;

#include "EUSART.substance.c"

Eusart* getEUSART() {
	return (Eusart*)&NAMESPACE(eusart);
}

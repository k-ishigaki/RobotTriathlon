#include <xc.h>
#include "Hardware.h"
#include "EUSART.h"
// EUSARTの実体を利用する
#define USING_EUSART_SUBSTANCE
#define NAMESPACE(name) EUSART1_##name

RCSTAbits_t* NAMESPACE(rcsta) = (RCSTAbits_t*)&RCSTA1bits;
TXSTAbits_t* NAMESPACE(txsta) = (TXSTAbits_t*)&TXSTA1bits;
BAUDCONbits_t* NAMESPACE(baudcon) = (BAUDCONbits_t*)&BAUDCON1bits;
SPBRGbits_t* NAMESPACE(spbrg) = (SPBRGbits_t*)&SPBRG1bits;
RCREGbits_t* NAMESPACE(rcreg) = (RCREGbits_t*)&RCREG1bits;
TXREGbits_t* NAMESPACE(txreg) = (TXREGbits_t*)&TXREG1bits;

#include "EUSART.substance.c"

Eusart* getEUSART1() {
	return (Eusart*)&NAMESPACE(eusart);
}

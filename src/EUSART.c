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

#undef NAMESPACE

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

#undef NAMESPACE

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

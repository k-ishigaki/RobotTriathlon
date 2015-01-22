/*
 * ボーレートの設定をするためにはHardware.hの
 * 動作周波数が正しい値である必要がある
 */

#include <xc.h>
#include <stdlib.h>
#include "EUSART.h"
#include "Hardware.h"

// デフォルトのボーレート
#define DEFAULT_BAUD_RATE 9600


#define EUSART_RESET(rcsta_spen) {rcsta_spen=0;rcsta_spen=1;}
void EUSART_reset() {EUSART_RESET(RCSTAbits.SPEN);}
void EUSART1_reset() {EUSART_RESET(RCSTA1bits.SPEN);}
void EUSART2_reset() {EUSART_RESET(RCSTA2bits.SPEN);}

// (baud rate) = F_OSC / (16 * (n + 1))
// n = F_OSC / (16 * (baud rate)) - 1
#define EUSART_SETBAUDRATE(brgh,brg16,spbrg) {\
	brgh = 0;\
	brg16 = 1;\
	spbrg = OPERATING_FREQUENCY / (16 * baudRate) - 1;\
}

void EUSART_setBaudRate(unsigned long baudRate) {
	EUSART_SETBAUDRATE(TXSTAbits.BRGH,BAUDCONbits.BRG16,SPBRG);
}
void EUSART1_setBaudRate(unsigned long baudRate) {
	EUSART_SETBAUDRATE(TXSTA1bits.BRGH,BAUDCON1bits.BRG16,SPBRG1);
}
void EUSART2_setBaudRate(unsigned long baudRate) {
	EUSART_SETBAUDRATE(TXSTA2bits.BRGH,BAUDCON2bits.BRG16,SPBRG2);
}

#define EUSART_ENABLE(txen,spen) {\
	txen = 1;\
	spen = 1;\
}
void EUSART_enable() {
	EUSART_ENABLE(TXSTAbits.TXEN,RCSTAbits.SPEN);
}
void EUSART1_enable() {
	EUSART_ENABLE(TXSTA1bits.TXEN,RCSTA1bits.SPEN);
}
void EUSART2_enable() {
	EUSART_ENABLE(TXSTA2bits.TXEN,RCSTA2bits.SPEN);
}

#define EUSART_DISABLE(txen,spen) {\
	txen = 0;\
	spen = 0;\
}
void EUSART_disable() {
	EUSART_DISABLE(TXSTAbits.TXEN,RCSTAbits.SPEN);
}
void EUSART1_disable() {
	EUSART_DISABLE(TXSTA1bits.TXEN,RCSTA1bits.SPEN);
}
void EUSART2_disable() {
	EUSART_DISABLE(TXSTA2bits.TXEN,RCSTA2bits.SPEN);
}

#define EUSART_READ(rcreg) {\
	return rcreg;\
}
char EUSART_read() {
	EUSART_READ(RCREG);
}
char EUSART1_read() {
	EUSART_READ(RCREG1);
}
char EUSART2_read() {
	EUSART_READ(RCREG2);
}

#define EUSART_WRITE(trmt, txreg) {\
	while(trmt == 1);\
	txreg = data;\
}
void EUSART_write(char data) {
	EUSART_WRITE(TXSTAbits.TRMT, TXREG);
}
void EUSART1_write(char data) {
	EUSART_WRITE(TXSTA1bits.TRMT, TXREG1);
}
void EUSART2_write(char data) {
	EUSART_WRITE(TXSTA2bits.TRMT, TXREG2);
}

Eusart eusart = {
	EUSART_reset,
	EUSART_setBaudRate,
	EUSART_enable,
	EUSART_disable,
	EUSART_read,
	EUSART_write,
};
//Eusart eusart1;
//Eusart eusart2;
Eusart* getEUSART() {return &eusart;}
//Eusart* getEUSART1() {return &eusart1;}
//Eusart* getEUSART2() {return &eusart2;}


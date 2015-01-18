/*
 * ボーレートの設定をするためにはHardwareImplication.hの
 * 動作周波数が正しい値である必要がある
 */

#include <xc.h>
#include <stdlib.h>
#include "EUSART.h"
#include "HardwareImplication.h"

// デフォルトのボーレート
#define DEFAULT_BAUD_RATE 9600

// Eusart構造体の定義
struct Eusart_t {
	enum EusartIdentifier id;
};

Eusart* getEUSART(enum EusartIdentifier e) {
	// 構造体ポインタの生成とIDの割り当て
	Eusart* this = (Eusart*)malloc(sizeof(Eusart));
	this->id = e;
	return this;
}

void EUSART_reset(Eusart* this) {
	switch (this->id) {
#if NUM_OF_EUSART == 1
		case EUSART:
			RCSTAbits.SPEN = 0;
			RCSTAbits.SPEN = 1;
			break;
#elif NUM_OF_EUSART == 2
		case EUSART1:
			RCSTA1bits.SPEN = 0;
			RCSTA1bits.SPEN = 1;
			break;
		case EUSART2:
			RCSTA2bits.SPEN = 0;
			RCSTA2bits.SPEN = 1;
			break;
#endif
	}
}

bool EUSART_setBaudRate(Eusart* this, uint_fast32_t baudRate) {
	// ボーレートが設定できない値であるときは失敗
	// OPERATING_FREQUENCYの設定によってはこの範囲内でも動作しないことがあるので注意
	if (baudRate > 4000000L || baudRate < 300L) return false;
	// (baud rate) = F_OSC / (16 * (n + 1))
	// n = F_OSC / (16 * (baud rate)) - 1
	unsigned int n = OPERATING_FREQUENCY / (16 * baudRate) - 1;
	switch (this->id) {
#if NUM_OF_EUSART == 1
		case EUSART:
			TXSTAbits.BRGH = 0;			 // Low Speed
			BAUDCONbits.BRG16 = 1;			 // 16-bit Baud Rate Generater
			SPBRG = n;
			break;
#elif NUM_OF_EUSART == 2
		case EUSART1:
			TXSTA1bits.BRGH = 0;			// Low Speed
			BAUDCON1bits.BRG16 = 1;			// 16-bit Baud Rate Generater
			SPBRG1 = n;
			break;
		case EUSART2:
			TXSTA2bits.BRGH = 0;			// Low Speed
			BAUDCON2bits.BRG16 = 1;			// 16-bit Baud Rate Generater
			SPBRG2 = n;
			break;
#endif
	}
	return true;
}

void EUSART_enable(Eusart* this) {
	switch (this->id) {
#if NUM_OF_EUSART == 1
		case EUSART:
			TXSTAbits.TXEN = 1;
			RCSTAbits.SPEN = 1;
			break;
#elif NUM_OF_EUSART == 2
		case EUSART1:
			TXSTA1bits.TXEN = 1;
			RCSTA1bits.SPEN = 1;
			break;
		case EUSART2:
			TXSTA2bits.TXEN = 1;
			RCSTA2bits.SPEN = 1;
			break;
#endif
	}
}

void EUSART_disable(Eusart* this) {
	switch (this->id) {
#if NUM_OF_EUSART == 1
		case EUSART:
			TXSTAbits.TXEN = 0;
			RCSTAbits.SPEN = 0;
			break;
#elif NUM_OF_EUSART == 2
		case EUSART1:
			TXSTA1bits.TXEN = 0;
			RCSTA1bits.SPEN = 0;
			break;
		case EUSART2:
			TXSTA2bits.TXEN = 0;
			RCSTA2bits.SPEN = 0;
			break;
#endif
	}
}

uint_fast8_t EUSART_read(Eusart *this) {
	switch (this->id) {
#if NUM_OF_EUSART == 1
		case EUSART:
			return RCREG;
#elif NUM_OF_EUSART == 2
		case EUSART1:
			return RCREG1;
		case EUSART2:
			return RCREG2;
#endif
		default:
			return 0;
	}
}

void EUSART_write(Eusart *this, uint_fast8_t data) {
	switch (this->id) {
#if NUM_OF_EUSART == 1
		case EUSART:
			while (TXSTAbits.TRMT == 1);
			TXREG = data;
			return;
#elif NUM_OF_EUSART == 2
		case EUSART1:
			while (TXSTA1bits.TRMT == 1);
			TXREG1 = data;
			return;
		case EUSART2:
			while (TXSTA2bits.TRMT == 1);
			TXREG2 = data;
			return;
#endif
		default:
			return;
	}
}

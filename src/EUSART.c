#include <xc.h>
#include <stdio.h>
#include "EUSART.h"

#define DEFAULT_BAUD_RATE 9600

// フラグ
typedef struct{
	unsigned portEnabled		:1;
	unsigned RXInterruptEnabled	:1;
	unsigned TXInterruptEnabled	:1;
} Flags;

// Eusart構造体の定義
struct Eusart_t{
	unsigned long baudRate;
	Flags flags;
} eusart1, eusart2;

Eusart* getEUSART(enum EusartIdentifier e) {
	Eusart *this = NULL;
	switch(e) {
		case EUSART1:
			this = &eusart1;
		case EUSART2:
			this = &eusart2;
	}
	this->baudRate = DEFAULT_BAUD_RATE;
	this->flags.portEnabled = 0;
	this->flags.RXInterruptEnabled = 0;
	this->flags.TXInterruptEnabled = 0;
	return this;
}

char EUSART_open(Eusart *this, long baudRate) {
	// ポートを開く前にリセットする
	EUSART_reset(this);
	// ボーレートを設定
	char isSuccess = EUSART_setBaudRate(this, baudRate);
	if(!isSuccess) {
		// ボーレートの設定に失敗したとき
		// 何もせず戻る
		return 0;					// 0:失敗
	}
	// ポートを有効にする
	EUSART_enableSerialPort(this);
	return 1;						// 1:成功
}

void EUSART_reset(Eusart *this) {

}

char EUSART_setBaudRate(Eusart *this, unsigned long baudRate) {
	return 0;
}

unsigned long EUSART_getBaudRate(Eusart *this) {
	return 0L;
}

void EUSART_enableSerialPort(Eusart *this) {

}

void EUSART_disableSerialPort(Eusart *this) {

}

void EUSART_enableRXInterrupt(Eusart *this) {

}

void EUSART_disableRXInterrupt(Eusart *this) {

}

void EUSART_enableTXInterrupt(Eusart *this) {

}

void EUSART_disableTXInterrupt(Eusart *this) {

}

char EUSART_receive(Eusart *this, char *data) {
	return 0;
}

char EUSART_transmit(Eusart *this, char data) {
	return 0;
}

char EUSART_Received(Eusart *this) {
	return 0;
}

char EUSART_isTXBufferEmpty(Eusart *this) {
	return 0;
}

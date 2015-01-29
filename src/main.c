#include <xc.h>	// xc8 projects must use this header file
#include "Hardware.h"
/**
 * ロボットトライアスロン用のプログラム
 */
int main(void) {	// use int type for CCI interface
	Eusart* serial = getEUSART1();
	serial->reset();
	GPIOPort* port = getPORTA();
	port->setDigitalOutput(0xFF);
	port->setValue(0xFF);
	GPIOPin* gpioPin = getRA0();
	DigitalPin* digitalPin = gpioPin->getDigitalPin();
	digitalPin->setDigitalOutput();
	digitalPin->setValue(1);
	AnalogPin* analogPin = gpioPin->getAnalogPin();
	analogPin->setAnalogInput();
	di();	// disable interrupt
	ei();	// enable interrupt
}

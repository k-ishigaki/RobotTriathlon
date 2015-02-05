/*
 * ロボットトライアスロン用のプログラム
 * とりあえずLチカ
 */

#include <xc.h>
#include <stdbool.h>
// Hardwareモジュールのインクルード
#include "Hardware.h"

#define _XTAL_FREQ 64000000L

int main(void) {
	OscillatorModule* oscillatorModule = getOscillatorModule();
	oscillatorModule->getPhaseLockedLoop()->enablePLL();
	oscillatorModule->getInternalOscillator()->setFrequency(16000000L);
	oscillatorModule->selectSystemClock(PRIMARY);
	DigitalPin* led = getRA0()->getDigitalPin();
	led->setDigitalOutput();
	while(true) {
		led->setValue(true);
		for (unsigned char i=0; i<100; i++) {
			__delay_ms(10);
		}
		led->setValue(false);
		for (unsigned char i=0; i<100; i++) {
			__delay_ms(10);
		}
	}
//	Eusart* serial = getEUSART1();
//	serial->reset();
//	GPIOPort* port = getPORTA();
//	port->setDigitalOutput(0xFF);
//	port->setValue(0xFF);
//	GPIOPin* gpioPin = getRA0();
//	DigitalPin* digitalPin = gpioPin->getDigitalPin();
//	digitalPin->setDigitalOutput();
//	digitalPin->setValue(1);
//	AnalogPin* analogPin = gpioPin->getAnalogPin();
//	analogPin->setAnalogInput();
//	di();	// disable interrupt
//	ei();	// enable interrupt
}

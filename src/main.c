/*
 * ロボットトライアスロン用のプログラム
 * とりあえずLチカ
 */

#include <xc.h>
#include <stdbool.h>
// Hardwareモジュールのインクルード
#include "Hardware.h"

#define _XTAL_FREQ 64000000L

// function prototype
void setup(void);
void loop(void);

// instance of Object
DigitalPin* led;

int main(void) {
	setup();
	while (true) {
		loop();
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

void setup() {
	// Oscillator settings
	OscillatorModule* osc = getOscillatorModule();
	osc->getPhaseLockedLoop()->enablePLL();
	osc->getInternalOscillator()->setFrequency(16000000L);
	osc->selectSystemClock(PRIMARY);
	// LED Pin settings
	led = getRA0()->getDigitalPin();
	led->setDigitalOutput();
}

void loop() {
	led->setValue(true);
	for (unsigned char i=0; i<100; i++) {
		__delay_ms(10);
	}
	led->setValue(false);
	for (unsigned char i=0; i<100; i++) {
		__delay_ms(10);
	}
}

/*
 * ロボットトライアスロン用のプログラム
 * とりあえずLチカ
 */

#include <xc.h>
#include <stdbool.h>
// Hardwareモジュールのインクルード
#include "Hardware.h"
#include "SerialPort.h"

#define _XTAL_FREQ 64000000L

// function prototype
void setup(void);
void loop(void);

// instance of Object
DigitalPin* led;
SerialPort* serial;

int main(void) {
	setup();
	while (true) {
		loop();
	}
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
	serial = getSerialPort(
			getRC7()->getDigitalPin(),
			getRC6()->getDigitalPin(),
			getEUSART1(),
			9600);
}

void loop() {
	led->setValue(true);
	serial->getByteOutputStream()->write('A');
	for (unsigned char i=0; i<100; i++) {
		__delay_ms(10);
	}
	led->setValue(false);
	serial->getByteOutputStream()->write('B');
	for (unsigned char i=0; i<100; i++) {
		__delay_ms(10);
	}
}

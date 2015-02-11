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
	// Serial Port settings
	serial = getSerialPort(
			getRC7()->getDigitalPin(),
			getRC6()->getDigitalPin(),
			getEUSART1(),
			115200);
	// interrupt settings
	RCONbits.IPEN = 1;
	IPR1bits.RC1IP = 0;
	IPR1bits.TX1IP = 0;
	INTCONbits.GIEL = 1;
	INTCONbits.GIEH = 1;
}

void interrupt high_priority isr_high() {
	// do nothing
}

void interrupt low_priority isr_low() {
	EUSART1_handleInterrupt();
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

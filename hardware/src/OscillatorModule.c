#include <xc.h>
#include "Hardware.h"

#define OscillatorModule_osccon OSCCONbits
#define OscillatorModule_osctune OSCTUNEbits
#define NAMESPACE(name) OscillatorModule_##name

static void NAMESPACE(selectSystemClock)(int clockSource) {
	switch ((OscillatorModule_clockSource)clockSource) {
		case INTERNAL:
			NAMESPACE(osccon).SCS = 0b10;
			break;
		case SECONDARY:
			NAMESPACE(osccon).SCS = 0b01;
			break;
		case PRIMARY:
			NAMESPACE(osccon).SCS = 0b00;
			break;
	}
}

static void NAMESPACE(setFrequency)(unsigned long frequency) {
	switch (frequency) {
		case 16000000L:
			NAMESPACE(osccon).IRCF = 0b111;
			break;
		case 8000000L:
			NAMESPACE(osccon).IRCF = 0b110;
			break;
		case 4000000L:
			NAMESPACE(osccon).IRCF = 0b101;
			break;
		case 2000000L:
			NAMESPACE(osccon).IRCF = 0b100;
			break;
		case 1000000L:
			NAMESPACE(osccon).IRCF = 0b011;
			break;
		case 500000L:
			NAMESPACE(osccon).IRCF = 0b010;
			break;
		case 250000L:
			NAMESPACE(osccon).IRCF = 0b001;
			break;
		case 31250L:
			NAMESPACE(osccon).IRCF = 0b000;
			break;
	}
}

static InternalOscillator NAMESPACE(internalOscillator) = {
	NAMESPACE(setFrequency),
};

static InternalOscillator* NAMESPACE(getInternalOscillator)() {
	return &NAMESPACE(internalOscillator);
}

static void NAMESPACE(enablePLL)() {
	NAMESPACE(osctune).PLLEN = 1;
}

static void NAMESPACE(disablePLL)() {
	NAMESPACE(osctune).PLLEN = 0;
}

static PhaseLockedLoop NAMESPACE(phaseLockedLoop) = {
	NAMESPACE(enablePLL),
	NAMESPACE(disablePLL),
};

static PhaseLockedLoop* NAMESPACE(getPhaseLockedLoop)() {
	return &NAMESPACE(phaseLockedLoop);
}

static OscillatorModule NAMESPACE(oscillatorModule) = {
	NAMESPACE(selectSystemClock),
	NAMESPACE(getInternalOscillator),
	NAMESPACE(getPhaseLockedLoop),
};

OscillatorModule* getOscillatorModule() {
	return &NAMESPACE(oscillatorModule);
}

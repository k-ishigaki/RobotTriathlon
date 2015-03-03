#ifdef USING_MSSP_MODULE_SUBSTANCE

#include <xc.h>

// common field variables

// --------------------------------------------------------------------
// I2CInterface
// --------------------------------------------------------------------
// field variables

// private field methods
static void NAMESPACE(generateStartCondition)() {
	NAMESPACE(SSPxCON2).SEN = 1;
	while (NAMESPACE(SSPxCON2).SEN == 1) {
		// wait
	}
	NAMESPACE(PIRx).SSPx(IF) = 0;
}

static void NAMESPACE(generateRestartCondition)() {
	NAMESPACE(SSPxCON2).RSEN = 1;
	while (NAMESPACE(SSPxCON2).RSEN == 1) {
		// wait
	}
	NAMESPACE(PIRx).SSPx(IF) = 0;
}

static void NAMESPACE(generateStopCondition)() {
	NAMESPACE(SSPxCON2).PEN = 1;
	while (NAMESPACE(SSPxCON2).PEN == 1) {
		// wait
	}
	NAMESPACE(PIRx).SSPx(IF) = 0;
}

static void NAMESPACE(checkInterruptFlag)() {
	while (NAMESPACE(PIRx).SSPx(IF) == 0) {
		// wait
	}
	NAMESPACE(PIRx).SSPx(IF) = 0;
}

// field methods
static void NAMESPACE(read)(uint8_t deviceAddress, uint8_t commandAddress, uint8_t size, uint8_t* buffer) {
	uint8_t initialSize = size;
	NAMESPACE(generateStartCondition)();
	// なぜintにキャストしていのかは不明
	NAMESPACE(SSPxBUF).SSPBUF = ((int)deviceAddress << 1) & 0b11111110;	// R/W! = 0 write
	NAMESPACE(checkInterruptFlag)();
	NAMESPACE(SSPxBUF).SSPBUF = commandAddress;
	NAMESPACE(checkInterruptFlag)();
	NAMESPACE(generateRestartCondition)();
	NAMESPACE(SSPxBUF).SSPBUF = ((int)deviceAddress << 1) | 0b00000001;	// R/W! = 1 read
	NAMESPACE(checkInterruptFlag)();

	while (size != 0) {
		NAMESPACE(SSPxCON2).RCEN = 1;	// start reception
		NAMESPACE(checkInterruptFlag)();
		buffer[initialSize - size--] = NAMESPACE(SSPxBUF).SSPBUF;	// read data
		NAMESPACE(SSPxCON2).ACKDT = 0; // ACKDT = 0 acknowledge
		if (size == 0) {
			NAMESPACE(SSPxCON2).ACKDT = 1; // ACKDT = 1 not acknowledge
		}
		NAMESPACE(SSPxCON2).ACKEN = 1;	// initiate acknowledge sequence
		NAMESPACE(checkInterruptFlag)();
	}
	NAMESPACE(generateStopCondition)();
}

static void NAMESPACE(write)(uint8_t deviceAddress, uint8_t commandAddress, uint8_t size, uint8_t* buffer) {
	NAMESPACE(generateStartCondition)();
	NAMESPACE(SSPxBUF).SSPBUF = ((int)deviceAddress << 1) & 0b11111110;	// R/W! = 0 write
	NAMESPACE(checkInterruptFlag)();
	NAMESPACE(SSPxBUF).SSPBUF = commandAddress;
	NAMESPACE(checkInterruptFlag)();
	for (char i=0; i<size; i++) {
		NAMESPACE(SSPxBUF).SSPBUF = buffer[i];
		NAMESPACE(checkInterruptFlag)();
	}
	NAMESPACE(generateStopCondition)();
}

// substance of interface
static I2CInterface NAMESPACE(i2cInterface) = {
	NAMESPACE(read),
	NAMESPACE(write),
};

// constructor
static I2CInterface* NAMESPACE(getI2CInterface)() {
	return &NAMESPACE(i2cInterface);
}

// --------------------------------------------------------------------
// I2CInterface
// --------------------------------------------------------------------
// substance of interface
static MSSPModule NAMESPACE(msspModule) = {
	NAMESPACE(getI2CInterface),
};


// constructor
MSSPModule* NAMESPACE(getter)(DigitalPin* sda, DigitalPin* scl) {
	sda->setDirection(false);
	scl->setDirection(false);

	// I2Cの初期化
	NAMESPACE(SSPxADD).SSPADD = 79;
	NAMESPACE(SSPxCON1).SSPEN = 1;
	NAMESPACE(SSPxCON1).SSPM = 0b1000;
	// 割り込みは使用しない
	NAMESPACE(PIRx).SSPx(IF) = 0;
	return &NAMESPACE(msspModule);
}

#undef NAMESPACE
#undef SSPx

#endif /* USING_MSSP_MODULE_SUBSTANCE */

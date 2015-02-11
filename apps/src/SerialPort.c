#include "SerialPort.h"
#include "Hardware.h"

#define NAMESPACE(name) SerialPort_##name

Eusart* NAMESPACE(uart);

static void NAMESPACE(onReceived)(uint8_t data) {
	DigitalPin* testPin = getRA1()->getDigitalPin();
	testPin->setDigitalOutput();
	if (data == 'A') {
		testPin->setValue(true);
	} else {
		testPin->setValue(false);
	}
}

static uint8_t NAMESPACE(onTransmitted)() {
	return 0;
}

EusartInterruptListener NAMESPACE(listener) = {
	NAMESPACE(onReceived),
	NAMESPACE(onTransmitted),
};

static uint8_t NAMESPACE(read)() {
	return NAMESPACE(uart)->read();
}

static ByteInputStream NAMESPACE(byteInputStream) = {
	NAMESPACE(read),
};

static void NAMESPACE(write)(uint8_t data) {
	NAMESPACE(uart)->write(data);
}

static ByteOutputStream NAMESPACE(byteOutputStream) = {
	NAMESPACE(write),
};

static ByteInputStream* NAMESPACE(getByteInputStream)() {
	return &NAMESPACE(byteInputStream);
}

static ByteOutputStream* NAMESPACE(getByteOutputStream)() {
	return &NAMESPACE(byteOutputStream);
}

static SerialPort NAMESPACE(serialPort) = {
	NAMESPACE(getByteInputStream),
	NAMESPACE(getByteOutputStream),
};

SerialPort* getSerialPort(
		DigitalPin* rxPin,
		DigitalPin* txPin,
		Eusart* uart,
		unsigned long baudRate) {
	NAMESPACE(uart) = uart;
	// rxのピンもデジタル入力にする必要がある
	rxPin->setDigitalInput();
	txPin->setDigitalInput();
	NAMESPACE(uart)->setBaudRate(baudRate);
	NAMESPACE(uart)->enable();
	NAMESPACE(uart)->addInterruptListener(&NAMESPACE(listener));
	NAMESPACE(uart)->enableRXInterrupt();
	return &NAMESPACE(serialPort);
}


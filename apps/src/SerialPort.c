#include "SerialPort.h"
#include "Hardware.h"

#define NAMESPACE(name) SerialPort_##name

Eusart* NAMESPACE(uart);
DigitalPin* NAMESPACE(rxPin);
DigitalPin* NAMESPACE(txPin);

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
	NAMESPACE(rxPin) = rxPin;
	NAMESPACE(txPin) = txPin;
	NAMESPACE(uart) = uart;
	// rxのピンもデジタル出力にする必要がある
	NAMESPACE(rxPin)->setDigitalOutput();
	NAMESPACE(txPin)->setDigitalOutput();
	NAMESPACE(uart)->setBaudRate(baudRate);
	NAMESPACE(uart)->enable();
	return &NAMESPACE(serialPort);
}


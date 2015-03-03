#include "LineSensor.h"

#define NAMESPACE(name) LineSensor_##name
#define LineSensor_getter getLineSensor


// field variables
I2CInterface* NAMESPACE(i2c);

static LineState NAMESPACE(getLineState)() {
	uint8_t buffer[1];
	NAMESPACE(i2c)->read('l', 0x07, 1, buffer);
	return (LineState)(buffer[0]);
}

static int NAMESPACE(getLineValue)() {
	uint8_t buffer[2];
	NAMESPACE(i2c)->read('l', 0x06, 2, buffer);
	return (buffer[0] + ((int)(buffer[1])<<8) - 2048;
}

// substance of interface
static LineSensor NAMESPACE(lineSensor) = {
	NAMESPACE(getLineState),
	NAMESPACE(getLineValue),
};


// constructor
LineSensor* NAMESPACE(getter)(I2CInterface* i2c) {
	NAMESPACE(i2c) = i2c;
	return &NAMESPACE(lineSensor);
}






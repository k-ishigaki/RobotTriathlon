#ifndef GPIO_PIN_H
#define GPIO_PIN_H

typedef void (*DigitalPin_setDigitalInput)();
typedef void (*DigitalPin_setDigitalOutput)();
typedef unsigned char (*DigitalPin_getValue)(void);
typedef void (*DigitalPin_setValue)(unsigned char value);

typedef void (*AnalogPin_setAnalogInput)();
typedef void (*AnalogPin_setAnalogOutput)();

typedef struct {
	DigitalPin_setDigitalInput setDigitalInput;
	DigitalPin_setDigitalOutput setDigitalOutput;
	DigitalPin_getValue getValue;
	DigitalPin_setValue setValue;
} GPIOPin;

typedef struct {
	DigitalPin_setDigitalInput setDigitalInput;
	DigitalPin_setDigitalOutput setDigitalOutput;
	DigitalPin_getValue getValue;
	DigitalPin_setValue setValue;
} DigitalPin;

typedef struct {
	DigitalPin_setDigitalInput setDigitalInput;
	DigitalPin_setDigitalOutput setDigitalOutput;
	DigitalPin_getValue getValue;
	DigitalPin_setValue setValue;
	AnalogPin_setAnalogInput setAnalogInput;
	AnalogPin_setAnalogOutput setAnalogOutput;
} AnalogPin;

#endif /* GPIO_PIN_H */

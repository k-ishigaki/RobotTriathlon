#ifdef USING_PWM_OUTPUTTER_SUBSTANCE

// --------------------------------------------------------------------
// PWMOutputter
// --------------------------------------------------------------------
// field variables
DigitalPin* NAMESPACE(pin1);
DigitalPin* NAMESPACE(pin2);
//EnhancedPWMDriver* NAMESPACE(driver);

// field methods
static void NAMESPACE(enablePWMOutput)() {
	NAMESPACE(pin1)->setDirection(true);
	NAMESPACE(pin2)->setDirection(true);
}

static void NAMESPACE(disablePWMOutput)() {
	NAMESPACE(pin1)->setDirection(false);
	NAMESPACE(pin2)->setDirection(false);
}

// substance of interface
static PWMOutputter NAMESPACE(pwmOutputter) = {
	NAMESPACE(enablePWMOutput),
	NAMESPACE(disablePWMOutput),
};

// constructor

PWMOutputter* NAMESPACE(getter)(DigitalPin* pin1, DigitalPin* pin2, EnhancedPWMDriver* driver) {

	driver->setPWMOutputMode(ENHANCED_PWM_DRIVER_MODE_HALF_BRIDGE, ENHANCED_PWM_DRIVER_OUTPUT_MODE_ACTIVE_HIGH_ACTIVE_HIGH);
	driver->setPWMDutyCount(50*4);

	NAMESPACE(pin1) = pin1;
	NAMESPACE(pin2) = pin2;

	NAMESPACE(disablePWMOutput)();

	return &NAMESPACE(pwmOutputter);
}

#undef NAMESPACE

#endif /* USING_PWM_OUTPUTTER_SUBSTANCE */

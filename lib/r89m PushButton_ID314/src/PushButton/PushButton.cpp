/*
 * PushButton.cpp
 *
 * Created: 18/11/2014 19:33:23
 *  Author: Richard
 */ 

#include "PushButton.h"

PushButton::PushButton(uint8_t pin){
	
	init(pin, ENABLE_INTERNAL_PULLUP);
}

PushButton::PushButton(uint8_t pin, uint8_t options){
	
	init(pin, options);
}

void PushButton::init(uint8_t pin, uint8_t options){
	
	if (options & ENABLE_INTERNAL_PULLUP){
		pinMode(pin, INPUT_PULLUP);
	} else {
		pinMode(pin, INPUT);
	}

	if (options & PRESSED_WHEN_LOW || options & ENABLE_INTERNAL_PULLUP){
		_button_pressed_value = LOW;
	}
	else {
		_button_pressed_value = HIGH;
	}

	// Default configuration for Debounced pin
	bouncer = Bounce();
	bouncer.attach(pin);
}

void PushButton::configureButton(PushButtonConfigurationCallback configurationCallback){
	
	configurationCallback(bouncer);	
}

boolean PushButton::_update_button_state(){
	
	// Update the button
	bouncer.update();
	// Return whether it is pressed or not
	return (bouncer.read() == _button_pressed_value);
}
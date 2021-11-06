/*
 * BasicButton.cpp
 *
 * Created: 18/11/2014 19:33:02
 *  Author: Richard
 */ 

#include <BasicButton.h>

BasicButton::BasicButton(uint8_t pin){
	
	_pin = pin;
	pinMode(_pin, INPUT);
}

boolean BasicButton::_update_button_state(){
	
	return (digitalRead(_pin) == HIGH);
}
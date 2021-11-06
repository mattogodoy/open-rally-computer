/*
 * PushButton.h
 *
 * Created: 18/11/2014 19:33:33
 *  Author: Richard
 */ 


#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

#include <Bounce2.h>
#include "Button.h"

#define PRESSED_WHEN_HIGH B0
#define PRESSED_WHEN_LOW B1
#define ENABLE_INTERNAL_PULLUP B10

// Define button configuration callback
typedef void (*PushButtonConfigurationCallback)(Bounce&);

class PushButton : public Button {
	
	private:
		Bounce bouncer;
		void init(uint8_t, uint8_t);

		uint8_t _button_pressed_value;
		
	protected:
		boolean _update_button_state();
	
	public:
		PushButton(uint8_t);
		PushButton(uint8_t, uint8_t);
	
		void configureButton(PushButtonConfigurationCallback);
};

#endif /* PUSHBUTTON_H_ */
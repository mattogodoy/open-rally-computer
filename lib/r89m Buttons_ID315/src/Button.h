/*
 * Button.h
 *
 * Created: 18/11/2014 19:33:02
 *  Author: Richard
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include <inttypes.h>
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// The maximum number of callbacks available to each button. A higher number will use more memory and be (slightly) slower
#define MAX_CALLBACKS_PER_BUTTON 3

// Forward reference
class Button;

// Define callback types
typedef void (*ButtonOnPressCallback)(Button&);
typedef void (*ButtonOnEventCallback)(Button&, uint16_t);
typedef void (*ButtonOnEventRepeatCallback)(Button&, uint16_t, uint16_t);

typedef enum {evtUninitialised, evtRelease, evtHold, evtHoldRepeat} EventType;
typedef enum {attSuccessful, attNoMoreRoom} CallbackAttachedResponse;

#include "ButtonEventCallback.h"

class Button{
	
	private:
		uint32_t _button_pressed_timestamp;								// When the button was originally pressed
		boolean _is_pressed;											// Whether or not the button is currently pressed
		
		ButtonOnPressCallback _on_press_callback;						// A callback for when the button is initially pressed
		ButtonEventCallback _eventCallbacks[MAX_CALLBACKS_PER_BUTTON];	// An array of callbacks for Release, Hold and HoldRepeat events
		
		void _button_pressed();
		void _button_released();
		void _button_held();
		uint16_t _button_time_elapsed();
		void _execute_callbacks(boolean);
		ButtonEventCallback* getNextAvailableCallback();
		
	protected:
		virtual boolean _update_button_state()=0;
	
	public:
		Button();
		void onPress(ButtonOnPressCallback);
		CallbackAttachedResponse onRelease(ButtonOnEventCallback);
		CallbackAttachedResponse onRelease(uint16_t, ButtonOnEventCallback);
		CallbackAttachedResponse onRelease(uint16_t, uint16_t, ButtonOnEventCallback);
		CallbackAttachedResponse onHold(uint16_t, ButtonOnEventCallback);
		CallbackAttachedResponse onHoldRepeat(uint16_t, uint16_t, ButtonOnEventRepeatCallback);
		
		boolean update();
		boolean is(Button&);
		boolean isPressed();
};
  
#endif /* BUTTON_H_ */
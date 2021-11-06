/*
 * Button.h
 *
 * Created: 18/11/2014 19:33:02
 *  Author: Richard
 */ 


#ifndef BUTTONEVENTCALLBACK_H
#define BUTTONEVENTCALLBACK_H

#include <inttypes.h>
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Button.h>

class ButtonEventCallback{
	
	private:
		EventType _type;
		uint16_t _delay;
		uint16_t _max_delay;
		uint16_t _repeat_period;
		uint8_t _execution_count;
	
		void calculateNextExecutionTime();
	
		// Callbacks
		ButtonOnEventCallback _callback;
		ButtonOnEventRepeatCallback _callback_repeating;
	
		// Keep track of when the callback should be executed
		uint16_t _next_execution_time;
	
	public:
		ButtonEventCallback();
		
		EventType getType();
		
		void setType(EventType);
		void setDelay(uint16_t);
		void setMaxDelay(uint16_t);
		void setRepetitionPeriod(uint16_t);
		void setCallback(ButtonOnEventCallback);
		void setRepeatingCallback(ButtonOnEventRepeatCallback);
		
		void executeCallbackIfTime(uint16_t, boolean, Button&);
		void reset();
	
};

#endif // BUTTONEVENTCALLBACK_H
/*
 * ButtonEventCallback.cpp
 *
 * Created: 18/11/2014 19:33:09
 *  Author: Richard
 */ 
 
 #include "Button.h"
 #include "ButtonEventCallback.h"

// Empty default constructor
ButtonEventCallback::ButtonEventCallback(){
	
	// Initialise variables
	_type = evtUninitialised;
	_delay = 0;
	_max_delay = 0;
	_repeat_period = 0;
	_execution_count = 1;
	
	_next_execution_time = 0;
}

EventType ButtonEventCallback::getType(){
	
	return _type;
}

void ButtonEventCallback::setType(EventType type){
	
	_type = type;
}

void ButtonEventCallback::setDelay(uint16_t delay){
	
	_delay = delay;
}

void ButtonEventCallback::setMaxDelay(uint16_t max_delay){
	
	_max_delay = max_delay;
}

void ButtonEventCallback::setRepetitionPeriod(uint16_t repeat_period){
	
	_repeat_period = repeat_period;
}

void ButtonEventCallback::setCallback(ButtonOnEventCallback callback){
	
	_callback = callback;
}

void ButtonEventCallback::setRepeatingCallback(ButtonOnEventRepeatCallback callback_repeating){
	
	_callback_repeating = callback_repeating;
}

void ButtonEventCallback::executeCallbackIfTime(uint16_t elapsedTime, boolean release_event, Button& btn){
	
	// Only process callbacks that have been initialised
	if(_type != evtUninitialised){
		if (release_event && _type == evtRelease){ // Only check release callbacks at the right time.
			if(elapsedTime > _next_execution_time && elapsedTime < _max_delay && _execution_count == 1){
				if(_callback){
					_callback(btn, elapsedTime);
				}
			_execution_count++;
			}
		} else if (_type == evtHold){
			if(elapsedTime > _next_execution_time && _execution_count == 1){
				if(_callback){
					_callback(btn, elapsedTime);
				}
				_execution_count++;
			}
		} else if (_type == evtHoldRepeat){
			if(elapsedTime > _next_execution_time){
				if(_callback_repeating){
					_callback_repeating(btn, elapsedTime, _execution_count);
				}
				calculateNextExecutionTime();
				_execution_count++;
			}
		}
	}
}

void ButtonEventCallback::calculateNextExecutionTime(){
	
	_next_execution_time += _repeat_period;
}

void ButtonEventCallback::reset(){
	
	_execution_count = 1;
	_next_execution_time = _delay;
}
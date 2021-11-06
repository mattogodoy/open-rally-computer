/*
 * BasicButton.h
 *
 * Created: 18/11/2014 19:33:02
 *  Author: Richard
 */ 

#include <Button.h>

#ifndef BASICBUTTON_H_
#define BASICBUTTON_H_

class BasicButton : public Button{

	private:
	uint8_t _pin;
	
	protected:
	boolean _update_button_state();
	
	public:
	BasicButton(uint8_t);

};

#endif /* BASICBUTTON_H_ */
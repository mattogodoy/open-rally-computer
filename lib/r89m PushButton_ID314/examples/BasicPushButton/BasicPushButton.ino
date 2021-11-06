/*
 * PushButton example. This shows a basic example of how to register events with a button.
 */

#include <Button.h>
#include <ButtonEventCallback.h>
#include <PushButton.h>
#include <Bounce2.h>    // https://github.com/thomasfredericks/Bounce-Arduino-Wiring

// Create an instance of PushButton reading digital pin 5
PushButton button = PushButton(5);

void setup(){

        // Open up the serial port so that we can write to it
	Serial.begin(9600);

        // Configure the button as you'd like - not necessary if you're happy with the defaults
        button.configureButton(configurePushButton);

        // When the button is first pressed, call the function onButtonPressed (further down the page)
	      button.onPress(onButtonPressed);
        // Once the button has been held for 1 second (1000ms) call onButtonHeld. Call it again every 0.5s (500ms) until it is let go
        button.onHoldRepeat(1000, 500, onButtonHeld);
        // When the button is released, call onButtonReleased
        button.onRelease(onButtonReleased);
}

void loop(){
	// Check the state of the button
	button.update();
}

// Use this function to configure the internal Bounce object to suit you. See the documentation at: https://github.com/thomasfredericks/Bounce2/wiki
// This function can be left out if the defaults are acceptable - just don't call configureButton
void configurePushButton(Bounce& bouncedButton){

        // Set the debounce interval to 15ms - default is 10ms
        bouncedButton.interval(15);
}

// btn is a reference to the button that fired the event. That means you can use the same event handler for many buttons
void onButtonPressed(Button& btn){

	Serial.println("button pressed");
}

// duration reports back how long it has been since the button was originally pressed.
// repeatCount tells us how many times this function has been called by this button.
void onButtonHeld(Button& btn, uint16_t duration, uint16_t repeatCount){

	Serial.print("button has been held for ");
	Serial.print(duration);
	Serial.print(" ms; this event has been fired ");
	Serial.print(repeatCount);
	Serial.println(" times");
}

// duration reports back the total time that the button was held down
void onButtonReleased(Button& btn, uint16_t duration){

	Serial.print("button released after ");
	Serial.print(duration);
	Serial.println(" ms");
}

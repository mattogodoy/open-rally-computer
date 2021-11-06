/*
 * BasicButton example. This shows a very basic example of how to register events with a button.
 *
 * I don't recommend anybody actually use the BasicButton class as it doesn't provide any debouncing facilities or the
 * ability to enable internal pullups. It is just to give a very simple demonstration with no additional dependencies.
 * For a better option use the PushButton library from the Libraries menu
 */

#include <Button.h>
#include <ButtonEventCallback.h>
#include <BasicButton.h>

// Create an instance of BasicButton reading digital pin 5
BasicButton button = BasicButton(5);

void setup(){

    // Open up the serial port so that we can write to it
    Serial.begin(9600);

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

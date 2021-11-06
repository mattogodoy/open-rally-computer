# r89m Buttons
This library makes working with buttons easy.

Easily handle button events such as ```onPress```, ```onHold```, ```onHoldRepeat``` and ```onRelease```. The same callback functions can be used with multiple buttons, helping to keep your code cleaner and more manageable.

Swap button types whenever you want - there's currently 3 supported types - 
[```PushButton```](https://github.com/r89m/PushButton), 
[```CapacitiveButton```](https://github.com/r89m/CapacitiveButton) and 
[```MPR121Button```](https://github.com/r89m/MPR121Button) but it is easy to create your own.

## Examples
Here's some basic examples to show you just how easy using this library is!

```c++
#include <Button.h>
#include <ButtonEventCallback.h>
#include <BasicButton.h>

// Create an instance of BasicButton reading digital pin 5
BasicButton button = BasicButton(5);

void setup(){

    // When the button is first pressed, call the function onButtonPressed
    button.onPress(onButtonPressed);
}

void loop(){
    // Check the state of the button
    button.update();
}

void onButtonPressed(Button& btn){

    // The button was pressed - do something!
}
```

```c++
#include <Button.h>
#include <ButtonEventCallback.h>
#include <BasicButton.h>

// Create an instance of BasicButton reading digital pin 5
BasicButton button = BasicButton(5);

void setup(){

    // Open up the serial port so that we can write to it
    Serial.begin(9600);

    // When the button is first pressed, call the function onButtonPressed
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

```

## Built-in Button Types

### [PushButton](https://github.com/r89m/PushButton)
A simple push button debounced using the Bounce library

Check out the [examples!](https://github.com/r89m/PushButton/tree/master/examples)

### [CapacitiveButton](https://github.com/r89m/CapacitiveButton)
A capacitive touch button utilising the CapSense library

Check out the [examples!](https://github.com/r89m/CapacitiveButton/tree/master/examples)

### [MPR121Button](https://github.com/r89m/MPR121Button)
A capacitive touch button utilising the MPR121 touch switch IC

Check out the [examples!](https://github.com/r89m/MPR121Button/tree/master/examples)

### BasicButton (not recommended!)
A simple button using digitalRead() to determine the state of the button. Does not perform any kind of debouncing, so false positives and multiple calls are likely. Use PushButton instead for a simple button.

This is only included so that you can get an example up-and-running quickly without needing any other dependencies.

## Methods
### ```boolean update()```
Update the button state - this will call any callbacks that are necessary. Returns ```true``` if the state changes.

### ```boolean is(Button& btn)```
Return whether or not the button is the same as the ```btn``` passed

### ```boolean isPressed()```
Return whether or not the button is currently pressed.

## Callbacks
### ```CallbackAttachedResponse onPress(onPressCallbackFunction)```
```onPressCallbackFunction``` is a function which will be called as soon as the button is pressed. It must be defined with the parameters shown below
```c++
void callThisFunctionOnPress(Button& btn){
  // btn is a reference to the button that was pressed.
}
```


### ```CallbackAttachedResponse onRelease```
There are 3 variations of onRelease:

#### ```CallbackAttachedResponse onRelease(onReleaseCallbackFunction)```

```onReleaseCallbackFunction``` is a function which is called when the button is released. It must be defined with the parameters shown below
```c++
void callThisFunctionOnRelease(Button& btn, uint_16t duration){
  // btn is a reference to the button that was pressed
  // duration is how long the button was pressed for
}
```

#### ```CallbackAttachedResponse onRelease(uint_16t wait, onReleaseCallbackFunction)```

As above, plus:

```wait``` if the button is held for at-least ```wait```ms ```onReleaseCallbackFunction``` will be called.

#### ```CallbackAttachedResponse onRelease(uint_16t wait, uint_16t max_wait, onReleaseCallbackFunction)```

As above, plus:

```max_wait``` if the button is held for more than ```max_wait```ms ```onReleaseCallbackFunction``` will not be called.


### ```CallbackAttachedResponse onHold(uint_16t duration, onHoldCallbackFunction)```

```duration``` how long the button must be held before ```onHoldCallbackFunction``` is called.
```onHoldCallbackFunction``` is a function which is called when the button is held. It must be defined with the parameters shown below

```c++
void callThisFuntionOnHold(Button& btn, uint_16t duration){
  // btn is a reference to the button that was held
  // duration is how long the button was held for
}
```

### ```CallbackAttachedResponse onHoldAndRepeat(uint_16t duration, uint_16t repeat_every, onHoldAndRepeatCallbackFunction)```

```duration``` how long the button must be held before ```onHoldAndRepeatCallbackFunction``` is called.
```repeat_every``` how long to wait before ```onHoldAndRepeatCallbackFunction``` is called repeatedly.
```onHoldAndRepeatCallbackFunction``` is a function which is called repeatedly when the button is held. It must be defined with the parameters shown below

```c++
void callThisFunctionOnHoldAndRepeat(Button& btn, uint16_t duration, uint8_t repeat_count){
  // btn is a reference to the button that was held
  // duration is how long the button has been held for
  // repeat_count is the number of times the callback has been called
}
```

## Enums

### ```CallbackAttachedResponse```
```attSuccessful``` returned when a callback has successfully been attached

```attNoMoreRoom``` returned when a callback could not be attached because there is not enough room. Check ```MAX_CALLBACKS_PER_BUTTON```.

## Constants

### ```MAX_CALLBACKS_PER_BUTTON (default=3)```
Defines the maximum number of callbacks per button. Increasing this number will allow more callbacks but will use marginally more memory and processing power. This can be changed on a sketch by sketch basis, simply define ```#MAX_CALLBACKS_PER_BUTTON``` before your ```#include```s.

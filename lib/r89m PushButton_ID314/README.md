# r89m Push Button
This library makes working with push buttons easy.

Easily handle button events such as ```onPress```, ```onHold```, ```onHoldRepeat``` and ```onRelease```. The same callback functions can be used with multiple buttons, helping to keep your code cleaner and more manageable.

This library relies on you having both [r89m Buttons](https://github.com/r89m/Button) and [Bounce2](https://github.com/thomasfredericks/Bounce2) libraries downloaded and available to the Arduino IDE.

## Examples

Checkout the [examples](examples) folder to show you how easy it is to use!

## Methods
### ```boolean update()```
Update the button state - this will call any callbacks that are necessary. Returns ```true``` if the state changes.

### ```boolean is(Button& btn)```
Return whether or not the button is the same as the ```btn``` passed

### ```boolean isPressed()```
Return whether or not the button is currently pressed.

### ```void configureButton(configureButtonCallback)```
Allows the underlying button object to be configured on a per-button basis. Useful if you want to tinker with low-level features of the button interface; eg. Bounce.

```configureButtonCallback``` is a function which takes one parameter, a Bounce object.

```c++
void configureBounce2ButtonCallback(Bounce& bounceButton){
  // You can now access the underlying Bounce object, and use all the methods provided
  // ie
  bounceButton.setInterval(20); // Set the debouncing interval
}
```

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

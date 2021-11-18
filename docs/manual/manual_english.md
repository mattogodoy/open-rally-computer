# Open Rally Computer

## User manual


- Introduction
- Installation
   - Power
   - Command
- Switched on
- Screens
- Navigation between screens
   - Status bar
   - Odometer
   - Speed
   - Travel time
   - Course
- Setting
   - Access the configuration menu
   - Navigate within settings
   - Reset trip
   - Language
   - Accuracy
   - Units
   - Time zone
   - Backlight
   - Quickview
   - Invert Screen
   - GPS data
   - Update firmware
   - Version
   - Factory values


## Introduction

This is the user manual for the **Open Rally Computer**. Here you will find everything you need to install and get the most out of your new tripmaster.
If you have any suggestion for improvement to this manual, do not hesitate to reach us at <https://github.com/mattogodoy/open-rally-computer/>


## Installation

The **Open Rally Computer** allows a simple installation thanks to the fact that it works only with GPS, so it is not necessary to install magnetic wheel sensors.
The clamping screws are **5mm** and have a **37mm** gap between them, which allows it to be installed without problems on supports intended for other
devices like the _ICO_.

### Power

The **Open Rally Computer** runs on **12 volts**, so it can be connected directly to the battery of the motorcycle.
The use of a 1A fuse is recommended but not essential, since this device it has a very low electricity consumption.
**IMPORTANT**
The power cable has 3 smaller cables inside:

1. **Black**: POSITIVE (+)
2. **Blue**: NEGATIVE (-)
3. **Brown**: _not used, do not connect_


Contrary to common convention, **the black wire on the Open Rally Computer is positive**. This is one design decision that, although not standard, allows it to be powered with electricity distribution modules such as the _F2R Rallye Power Box_ or with power cables from other brands like the _ICO_.
Although the **Baja Pro** has a reverse polarity protection mechanism, it is It is advisable to pay special attention to the colors of the cables and connect them correctly.

### Command

To install the remote included with the **Baja Pro**, you must:

1. Remove the Allen screws that keep it closed.
2. Carefully open the two pieces that make up the body of the control (CAUTION, both pieces will be joined by a pair of cables).
3. Choose the direction of the cable exit: the control body has two notches; one on the right and one on the left. This allows the remote to be installed in any of the both sides of the handlebar.
4. Place the control on the handlebar of the motorcycle **taking special care that the cable does not remain pressed between the handlebar and the controller**.
5. Tighten the screws without exerting excessive pressure. The body of the controls is made of aluminum and excessive screw pressure could ruin the threads.
The remote has 3 buttons with different functions based on the screen on which you find:
- **Upper front**: Increase / Raise
- **Lower front**: Reduce / Lower
- **Rear**: Change screen / Partial reset / Access menu / Select


## Switched on

The **Baja Pro** does not have an on / off switch, so the management of the power is left to the pilot.
For reasons inherent to the operation of the GPS system, if the **Baja Pro** has not been used for a long period of time, or if it is turned on in a location far from where it was last used, it may take a few minutes for the device to get a signal from GPS satellites.
It is for this reason that it is advisable to always turn on the **Baja Pro** a few minutes before starting the tour.
That said, the **Baja Pro** is capable of obtaining positioning information from both the constellation of **GPS** satellites as well as **Glonass** and **Galileo**, which allows the satellite reception wait time is quite low and the accuracy is higher than that of other devices.

## Screens

The Baja Pro has several screens that show useful information when navigating using a roadbook. The distribution of information within the screens and the way in which that the data are grouped is designed to facilitate the pilot reading the data simply sight and with minimal effort.

## Navigating between screens

To change the screen, simply press the selection button on the remote (button rear)


### Status bar

At the top of all screens (except for the configuration screens) there is a bar of State.

In this bar you can see important information:
- In the left corner you can see a disc. If the disc is spinning it means that the GPS module is searching for satellites to get your location. Once you have obtained a reliable location, the disk icon will change to bars indicating the quality of the sign.
- In the center is the current time. The hour values ​​are obtained from the module GPS, so it has great precision. This implies that until there is no GPS signal, the time it is not correct. **IMPORTANT:** Remember to set the time zone of the place where you you find (_see time zone configuration section_).
- In the right corner you can see the number of satellites of which the GPS module receives signal. The minimum required to obtain a valid location is **4 satellites**, although in this case more is better.

### Odometer

The screen you will most likely see most of the time is the odometer.
In it you can see:
- **Total distance** in the upper left: Counts the distance traveled from the last total distance reset (from the configuration menu). This distance **does NOT** vary when manually adjusting the partial distance using the buttons. It can be considered as the total and real distance that you have traveled during a complete stage.
- **Partial distance** in the center: Counts the distance traveled since the last reset of partial distance.
- **Heading** in the upper right: The heading is indicated in degrees, with 0º being North and 180º the South.

**Controls**
On this screen, the remote control buttons fulfill the following functions:
- **Up**: Recalculates partial distance up (increases). If the precision of the distance is set to 1 decimal, adds 100 meters. If it is set to 2 decimal places, add 10 meters. Keeping the button pressed will quickly increase to do changes of great distances.
- **Down**: Recall partial distance down (reduce). If the distance accuracy is set to 1 decimal, subtract 100 meters. If it is set to 2 decimal places, subtract 10 meters. Keeping the button pressed will quickly zoom out to make changes of great distances.
- **Selection**: If pressed briefly, it switches to the next screen. If it stays pressed resets the partial distance to 0. This **DOES NOT** affect the total distance.

### Speed

On this screen you can see:
- The speed at which you are currently moving.
- The average speed since the last reset carried out from the configuration menu.
**NOTE**: This average includes the time the motorcycle is not moving. This is especially useful to know your real average the regularity rallies.
- The maximum speed reached since the last reset carried out from the settings menu setting. This value is useful to avoid being penalized in rallies where speed maximum is limited.
**Controls**
On this screen, the remote control buttons fulfill the following functions:
- **Up**: If the QuickView functionality is enabled, displays the Odometer screen while holding down the button.


`` ''
- Bottom: If the QuickView functionality is enabled, displays the Odometer screen while holding down the button.
- Selection: Short press switches to next screen. If it stays pressed it accesses the configuration screen.
`` ''
### Travel time

On this screen you can see the time elapsed since the last reset performed since the settings menu, including the time the motorcycle has been stopped. This is especially useful for regularity rallies.
**Controls**
On this screen, the remote control buttons fulfill the following functions:
- **Up**: If the QuickView functionality is enabled, displays the Odometer screen while holding down the button.
- **Down**: If QuickView functionality is enabled, displays the Odometer screen while holding down the button.
- **Selection**: If pressed briefly, it switches to the next screen. If it stays pressed it accesses the configuration screen.

### Course

Indicates the current heading in degrees, being 0º North and 180º South.
**NOTE**: Heading is calculated by drawing vectors between GPS location points, so this value is not valid if the motorcycle is not moving.
**Controls**
On this screen, the remote control buttons fulfill the following functions:
- **Up**: If the QuickView functionality is enabled, displays the Odometer screen while holding down the button.
- **Down**: If QuickView functionality is enabled, displays the Odometer screen while holding down the button.
- **Selection**: If pressed briefly, it switches to the next screen. If it stays pressed it accesses the configuration screen.

## Setting

This is the screen from which the **Baja Pro** is configured.

### Access the configuration menu

To access the configuration menu, I am **stating at any screen other than the Odometer**, press and hold the **Select** button (rear button of controller) for a few seconds.

### Navigate within settings

To select options within the setup menu using the knob:
- **Up**: Upper front button
- **Lower**: Lower front button
- **Select**: Back button
- **Cancel**: Press and hold the back button
- **Exit menu**: Press and hold the back button

### Reset trip

Use this option before starting each stage of a rally. This resets:
- Total distance
- Partial distance
- Average speed
- Maximum speed
- Travel time


### Language

The **Baja Pro** can be configured in the following languages:
- Spanish
- English
Select the one that best suits your needs.

### Accuracy

The accuracy level of the **Baja Pro** can be set between:
- **One decimal**: Distances show increments every 100 meters. Upon landing, will add or subtract 100 meters to the partial distance.
- **Two decimal places**: Distances show increments every 10 meters. Upon landing, will add or subtract 10 meters to the partial distance.

### Units

The **Baja Pro** unit system can be configured in:
- Metric (km / h, mm)
- Imperial (mph / in)
This option affects distance measurements. In the **Metric** system **kilometers** are used and in the
**Imperial** system **miles** are used.
**NOTE**: Changing this option resets all time, speed and distance values.

### Time zone

Allows you to select the time zone you are in to obtain a correct value for the current time.
The range of **UTC** values ​​is between **- 12** and **+ 14.**

### Backlight

Select how bright the screen is.
The range of values ​​is from **0** (light off) to **10** (maximum intensity). This is especially useful for low-light or night stages where the brightness of the display may affect the visibility of the pilot.

### Quickview

This functionality allows you to quickly and temporarily return to the home screen.
**Odometer** when you are on any other screen.
If this option is activated, whenever you are on a screen other than **Odometer**, at holding down the upper or lower button on the remote will temporarily display the **Odometer** display. Releasing the button on the controller will return to the screen where you you found previously.
This is especially useful for sections where you need to pay special attention to the **Heading** or **Speed ​​**, but from time to time you need to quickly see the distance traveled.

### Invert Screen

Allows you to invert the screen image 180º.
This is useful in case you have to install the **Baja Pro** in an inverted position.

### GPS data

Raw data from the GPS module among which you can find Latitude, Longitude, Height and more.
This could be useful in the event that you need to share your current location with somebody.


### Update firmware

Update the **Open Rally Computer** firmware to the latest version.
The description of this functionality will be updated in this manual as soon as a firmware update is released.

### Version

It shows the serial number of your device and its current firmware version.

### Factory settings

Restores the **Open Rally Computer** values and settings to their factory state.

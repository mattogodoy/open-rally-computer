/**************************************************************************/
/*!
    @file     FRAM_I2C_connect.ino
    @author   SOSAndroid (E. Ha.)
    @license  BSD (see license.txt)

    This sketch connects the FRAM chips and tries to identify it. This succeed if the IDs are known, fails otherwise

    @section  HISTORY

    v1.0.0 - First release

*/
/**************************************************************************/

#include <Wire.h>
#include <math.h>

#include <FRAM_MB85RC_I2C.h>


//Creating object for FRAM chip
FRAM_MB85RC_I2C mymemory;

void setup() {

	Serial.begin(9600);
	while (!Serial) ; //wait until Serial ready
	Wire.begin();
	
    Serial.println("Starting...");

	
	mymemory.begin();
	//While SERIAL_DEBUG enabled at the library level, this should output the device's IDs


}

void loop() {
	// nothing to do
}
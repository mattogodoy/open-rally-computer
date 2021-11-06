/**************************************************************************/
/*!
    @file     FRAM_I2C_simple_write_read.ino
    @author   SOSAndroid (E. Ha.)
    @license  BSD (see license.txt)

    Example sketch to write & read "automatic setting".

    @section  HISTORY

    v1.0.0 - First release
	V1.1.0 - Reworked code to test wider range of the memory
	
		
*/
/**************************************************************************/

#include <Wire.h>
#include <FRAM_MB85RC_I2C.h>


byte resultw, resultr; 
//dummy data used for the test
uint8_t writevalue = 0xBE;
uint8_t readvalue = 0xEF; // at the end, readvalue should be equal to writevalue


//random addresses to write from
uint16_t writeaddress = 0x025; // Beginning of the memory map


//Creating object for FRAM chip
FRAM_MB85RC_I2C mymemory();


void setup() {

	Serial.begin(115200);
	while (!Serial) ; //wait until Serial ready
	Wire.begin();
	
    Serial.println("Starting...");

	mymemory.begin();

//--------------------------- First run, beginning of memory map ---------------------
	Serial.println("1st test");
	Serial.print("Writing at location 0x");
	Serial.println(writeaddress, HEX);
	
    Serial.println("Writing...");
	resultw = mymemory.writeByte(writeaddress, writevalue);
	Serial.println("Reading...");
	resultr = mymemory.readByte(writeaddress, &readvalue);
	
	Serial.print("Written value 0x");
	Serial.println(writevalue, HEX);
	
	Serial.print("Read value 0x");
	Serial.println(readvalue, HEX);
	
	if (writevalue == readvalue) {
		Serial.println("Write Byte test : OK");
	}
	else {
		Serial.println("Write Byte test : NOT OK");
	}
	Serial.println(".... ....");
	
	
//------------------------- Device IDs -----------------------------------------------
	uint16_t id;
	resultr = mymemory.getOneDeviceID(1, &id);
	Serial.print("Manufacturer 0x");
	Serial.println(id, HEX);
	
	resultr = mymemory.getOneDeviceID(3, &id);
	Serial.print("DensityCode 0x");
	Serial.println(id, HEX);
	
	resultr = mymemory.getOneDeviceID(4, &id);
	Serial.print("Density ");
	Serial.println(id, DEC);

	
}

void loop() {
	// nothing to do
}
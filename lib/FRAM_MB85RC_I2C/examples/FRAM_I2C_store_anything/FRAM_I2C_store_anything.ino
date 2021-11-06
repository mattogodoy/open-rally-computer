/**************************************************************************/
/*!
    @file     FRAM_I2C_store_anything.ino
    @author   SOSAndroid (E. Ha.)
    @license  BSD (see license.txt)

    Example sketch that stores and retreive any kind of data.

    @section  HISTORY

    v1.0 - First release
	v1.0.1 - fix constructor call error
*/
/**************************************************************************/

#include <Wire.h>
#include <math.h>

#include <FRAM_MB85RC_I2C.h>


//define a struct of various data types
typedef struct MYDATA_t {
	bool data_0;
	float data_1; 
	long data_2; 
	int data_3;
	byte data_4;
};

//define a struct joining MYDATA_t to an array of bytes to be stored
typedef union MYDATA4I2C_t {
 MYDATA_t datastruct;
 uint8_t I2CPacket[sizeof(MYDATA_t)];
};

MYDATA4I2C_t mydata; //data to be written in memory
MYDATA4I2C_t readdata; //data read from memory

//random address to write from
uint16_t writeaddress = 0x025;

//Creating object for FRAM chip
FRAM_MB85RC_I2C mymemory;

void setup() {

	Serial.begin(9600);
	while (!Serial) ; //wait until Serial ready
	Wire.begin();
	
	byte arraySize = sizeof(MYDATA_t);
	
    Serial.println("Starting...");
		
	mymemory.begin();
		
	
//---------init data - load array
	mydata.datastruct.data_0 = true;
	Serial.print("Data_0: ");
	if (mydata.datastruct.data_0) Serial.println("true");
	if (!mydata.datastruct.data_0) Serial.println("false");
	mydata.datastruct.data_1 = 1.3575;
	Serial.print("Data_1: ");
	Serial.println(mydata.datastruct.data_1, DEC);
	mydata.datastruct.data_2 = 314159L;
	Serial.print("Data_2: ");
	Serial.println(mydata.datastruct.data_2, DEC);
	mydata.datastruct.data_3 = 142;
	Serial.print("Data_3: ");
	Serial.println(mydata.datastruct.data_3, DEC);	
	mydata.datastruct.data_4 = 0x50;
	Serial.print("Data_4: 0x");
	Serial.println(mydata.datastruct.data_4, HEX);
	Serial.println("...... ...... ......");
	Serial.println("Init Done - array loaded");
	Serial.println("...... ...... ......");



//----------write to FRAM chip
	byte result = mymemory.writeArray(writeaddress, arraySize, mydata.I2CPacket);

    if (result == 0) Serial.println("Write Done - array loaded in FRAM chip");
    if (result != 0) Serial.println("Write failed");
	Serial.println("...... ...... ......");
	
	
//---------read data from memory chip
	result = mymemory.readArray(writeaddress, arraySize, readdata.I2CPacket);
    if (result == 0) Serial.println("Read Done - array loaded with read data");
    if (result != 0) Serial.println("Read failed");
	Serial.println("...... ...... ......");
	
//---------Send data to serial
	Serial.print("Data_0: ");
	if (readdata.datastruct.data_0) Serial.println("true");
	if (!readdata.datastruct.data_0) Serial.println("false");
	Serial.print("Data_1: ");
	Serial.println(readdata.datastruct.data_1, DEC);
	Serial.print("Data_2: ");
	Serial.println(readdata.datastruct.data_2, DEC);
	Serial.print("Data_3: ");
	Serial.println(readdata.datastruct.data_3, DEC);	
	Serial.print("Data_4: 0x");
	Serial.println(readdata.datastruct.data_4, HEX);
	Serial.println("...... ...... ......");
	Serial.println("Read Write test done - check data if successfull");
	Serial.println("...... ...... ......");	

	
}

void loop() {
	// nothing to do
}
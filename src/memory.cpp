// Open Rally Computer
// Copyright (C) 2021  Matías Godoy

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.


#include <memory.h>
#include <Wire.h>
#include <FRAM_MB85RC_I2C.h>
#include <languages.h>
#include <units.h>

uint16_t mem_address = 0x025; // Define the memory address to write to

// FRAM memory object
FRAM_MB85RC_I2C fram_memory(0x50, false, 0, 4); // [chipAddress, writeProtectEnabled, wpPin, chipDensity (4, 16, 64, 128, 256, 512 or 1024)]
ConfigI2C memory = {};
TempConfig state = {};

void initMemory() {
  Wire.begin();
  fram_memory.begin();
}

void initializeConfig() {
  memory.config.avgAccumulator = 0;
  memory.config.avgSamples = 0;
  memory.config.language = LANG_ENGLISH;
  memory.config.declAngle = 0.01425352f; // Madrid
  memory.config.tripPartial = 0;
  memory.config.tripTotal = 0;
  memory.config.tripTime = 0;
  memory.config.maxSpeed = 0;
  memory.config.units = UNITS_METRIC;
  memory.config.timeZone = 0;
  memory.config.backlight = 10;
  memory.config.precision = 1;
  memory.config.quickViewEnabled = true;
  memory.config.flipScreen = false;
  memory.config.memoryInitialized = true;

  state.currentScreen = 0;
  state.menuCurrentSelection = 1;
  state.menuCurrentValue = 0;
  state.menuLastCommand = 0;
  state.menuCurrentLanguage = 1;
  state.inputValue = -99;
  state.units = 1;
  state.currentTemperature = 0;
  state.currentHeading = 0;
  state.currentSpeed = 0;
  state.average = 0;
  state.previousLatitude = 0;
  state.previousLongitude = 0;
  state.currentLatitude = 0;
  state.currentLongitude = 0;
  state.gpsSatellites = 0;
  state.currentAltitude = 0;
  state.timeHours = 0;
  state.timeMinutes = 0;
  state.timeSeconds = 0;
  state.gpsPrecision = 1000;
  state.gpsDataAge = 0;
  state.gpsFix = false;
  state.gpsCharsProcessed = 0;
  state.gpsLastSecond = 0;
  state.gpsDiscPos = 0;
  state.secsStopped = 0;
  state.alreadySaved = true;
  state.isMoving = false;
  state.selectButtonPressedSince = 0;
  state.quickViewScreen = 0;
  state.currentUpdateStep = 1;
  state.updatingFirmware = 0;
}

void resetConfig() {
  initializeConfig();
  saveConfig();
}

void loadConfig() {
  initMemory();
  byte arraySize = sizeof(Configuration);
  byte readResult = fram_memory.readArray(mem_address, arraySize, memory.I2CPacket);

  if (readResult == 0) {
    // Check if memory has been initialized
    if (memory.config.memoryInitialized != true) {
      // Initialize memory for the first time
      Serial.println(F("Memory has not been initialized. Setting memory structure..."));
      resetConfig();
      Serial.println(F("Reset performed - array loaded with initial memory"));
    }
  } else {
    Serial.println(F("====================>>> ERROR READING MEMORY!"));
    initializeConfig(); // Set config to an initial set of values
  }
}

void saveConfig() {
  byte arraySize = sizeof(Configuration);

  // writeArray returns 0 if all went well. Otherwise, an error ocurred while writing to memory.
  fram_memory.writeArray(mem_address, arraySize, memory.I2CPacket);
}

void dumpConfig() {
  Serial.println(F("=========================================================================="));
  Serial.print(F("memory.config.avgAccumulator: "));
  Serial.println(memory.config.avgAccumulator);
  Serial.print(F("memory.config.avgSamples: "));
  Serial.println(memory.config.avgSamples);
  Serial.print(F("memory.config.language: "));
  Serial.println(memory.config.language);
  Serial.print(F("memory.config.declAngle: "));
  Serial.println(memory.config.declAngle);
  Serial.print(F("memory.config.tripPartial: "));
  Serial.println(memory.config.tripPartial);
  Serial.print(F("memory.config.tripTotal: "));
  Serial.println(memory.config.tripTotal);
  Serial.print(F("memory.config.tripTime: "));
  Serial.println(memory.config.tripTime);
  Serial.print(F("memory.config.maxSpeed: "));
  Serial.println(memory.config.maxSpeed);
  Serial.print(F("memory.config.units: "));
  Serial.println(memory.config.units);
  Serial.print(F("memory.config.timeZone: "));
  Serial.println(memory.config.timeZone);
  Serial.print(F("memory.config.backlight: "));
  Serial.println(memory.config.backlight);
  Serial.print(F("memory.config.precision: "));
  Serial.println(memory.config.precision);
  Serial.print(F("memory.config.quickViewEnabled: "));
  Serial.println(memory.config.quickViewEnabled);
  Serial.print(F("memory.config.flipScreen: "));
  Serial.println(memory.config.flipScreen);
  Serial.print(F("memory.config.memoryInitialized: "));
  Serial.println(memory.config.memoryInitialized);
}

void dumpTempConfig() {
  Serial.println(F("=========================================================================="));
  Serial.print(F("state.currentScreen: "));
  Serial.println(state.currentScreen);
  Serial.print(F("state.menuCurrentSelection: "));
  Serial.println(state.menuCurrentSelection);
  Serial.print(F("state.menuCurrentValue: "));
  Serial.println(state.menuCurrentValue);
  Serial.print(F("state.menuLastCommand: "));
  Serial.println(state.menuLastCommand);
  Serial.print(F("state.menuCurrentLanguage: "));
  Serial.println(state.menuCurrentLanguage);
  Serial.print(F("state.inputValue: "));
  Serial.println(state.inputValue);
  Serial.print(F("state.units: "));
  Serial.println(state.units);
  Serial.print(F("state.currentTemperature: "));
  Serial.println(state.currentTemperature);
  Serial.print(F("state.currentHeading: "));
  Serial.println(state.currentHeading);
  Serial.print(F("state.currentSpeed: "));
  Serial.println(state.currentSpeed);
  Serial.print(F("state.average: "));
  Serial.println(state.average);
  Serial.print(F("state.previousLatitude: "));
  Serial.println(state.previousLatitude);
  Serial.print(F("state.previousLongitude: "));
  Serial.println(state.previousLongitude);
  Serial.print(F("state.currentLatitude: "));
  Serial.println(state.currentLatitude);
  Serial.print(F("state.currentLongitude: "));
  Serial.println(state.currentLongitude);
  Serial.print(F("state.gpsSatellites: "));
  Serial.println(state.gpsSatellites);
  Serial.print(F("state.currentAltitude: "));
  Serial.println(state.currentAltitude);
  Serial.print(F("state.timeHours: "));
  Serial.println(state.timeHours);
  Serial.print(F("state.timeMinutes: "));
  Serial.println(state.timeMinutes);
  Serial.print(F("state.timeSeconds: "));
  Serial.println(state.timeSeconds);
  Serial.print(F("state.gpsPrecision: "));
  Serial.println(state.gpsPrecision);
  Serial.print(F("state.gpsDataAge: "));
  Serial.println(state.gpsDataAge);
  Serial.print(F("state.gpsFix: "));
  Serial.println(state.gpsFix);
  Serial.print(F("state.gpsCharsProcessed: "));
  Serial.println(state.gpsCharsProcessed);
  Serial.print(F("state.gpsLastSecond: "));
  Serial.println(state.gpsLastSecond);
  Serial.print(F("state.gpsDiscPos: "));
  Serial.println(state.gpsDiscPos);
  Serial.print(F("state.secsStopped: "));
  Serial.println(state.secsStopped);
  Serial.print(F("state.alreadySaved: "));
  Serial.println(state.alreadySaved);
  Serial.print(F("state.isMoving: "));
  Serial.println(state.isMoving);
  Serial.print(F("state.selectButtonPressedSince: "));
  Serial.println(state.selectButtonPressedSince);
  Serial.print(F("state.quickViewScreen: "));
  Serial.println(state.quickViewScreen);
  Serial.print(F("state.currentUpdateStep: "));
  Serial.println(state.currentUpdateStep);
  Serial.print(F("state.updatingFirmware: "));
  Serial.println(state.updatingFirmware);
}
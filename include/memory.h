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


#pragma once

#include <Arduino.h>

// Define the data struct (various data types allowed)
struct Configuration {
  unsigned long avgAccumulator; // Speed samples added
  unsigned int avgSamples;      // Number of speed samples to calculate average
  unsigned int language;
  float declAngle;              // In degrees
  float tripPartial;            // In kilometers
  float tripTotal;              // In kilometers
  unsigned long tripTime;       // In seconds
  unsigned int maxSpeed;        // In km/h
  unsigned int units;
  int timeZone;                 // Between -12 and +14
  unsigned int backlight;       // Between 0 and 10
  unsigned int precision;
  bool quickViewEnabled;
  bool flipScreen;
  bool memoryInitialized;       // To know if the memory has been initialized for the first time
};

// Define a struct joining Configuration to an array of bytes to be stored
union ConfigI2C {
  Configuration config;
  uint8_t I2CPacket[sizeof(Configuration)];
};

extern ConfigI2C memory; // Data to be written in memory

// Storage for temporary config values
struct TempConfig {
  int currentScreen;
  int menuCurrentSelection;
  int menuCurrentValue;
  int menuLastCommand;
  int menuCurrentLanguage;
  int inputValue;
  int units;
  float currentTemperature;
  int currentHeading;
  int currentSpeed;
  int average;
  double previousLatitude;
  double previousLongitude;
  double currentLatitude;
  double currentLongitude;
  int gpsSatellites;
  int currentAltitude;
  int timeHours;
  int timeMinutes;
  int timeSeconds;
  int gpsPrecision;
  long gpsDataAge;
  bool gpsFix;
  unsigned long gpsCharsProcessed;
  int gpsLastSecond;
  int gpsDiscPos;
  int secsStopped;
  bool alreadySaved;
  bool isMoving;
  unsigned long selectButtonPressedSince;
  int quickViewScreen;
  int currentUpdateStep;
  int updatingFirmware;
};

extern TempConfig state;

void initializeConfig();
void resetConfig();
void loadConfig();
void saveConfig();
void dumpConfig();
void dumpTempConfig();

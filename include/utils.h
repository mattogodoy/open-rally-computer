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

int getCenterPosition(String str);
void drawStrIndexRightAligned(int strIndex, int padding, int y);
void drawStrRightAligned(String str, int padding, int y);
char* secondsToTimeString(unsigned long t);
char* secondsToHHMM(unsigned long t);
char* secondsToSS(unsigned long t);
String getSerialNumber();
float roundToOneDecimal(float value);
float celsiusToFarenheit(float celsius);

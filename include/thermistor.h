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

// Used Thermistor: MF52AT 1k

#define THERMISTOR_NOMINAL 1000  // resistance at 25 degrees C
#define TEMPERATURE_NOMINAL 25   // temp. for nominal resistance (almost always 25 C)
#define B_COEFFICIENT 3950       // The beta coefficient of the thermistor (usually 3000-4000)
#define SERIES_RESISTOR 1000     // the value of the 'other' resistor

void updateTemperature(void);

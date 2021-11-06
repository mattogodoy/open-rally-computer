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


#include <thermistor.h>
#include <Arduino.h>
#include <math.h>
#include <pins.h>
#include <memory.h>
#include <units.h>
#include <utils.h>

float analogVal;
float resistance;
float steinhart;
float celsius;


void updateTemperature(void) {
  analogVal = analogRead(PIN_THERMISTOR);
  resistance = 4095 / analogVal;                      // ESP32 ADC range is 12 bit (0 - 4095)
  resistance = SERIES_RESISTOR / resistance;
  steinhart = resistance / THERMISTOR_NOMINAL;        // (R/Ro)
  steinhart = log(steinhart);                         // ln(R/Ro)
  steinhart /= B_COEFFICIENT;                         // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURE_NOMINAL + 273.15);  // + (1/To)
  steinhart = 1 / steinhart;                          // Invert
  celsius = steinhart - 273.15;                       // convert Kelvin to C

  if (memory.config.units == UNITS_METRIC) { // Celsius
    state.currentTemperature = celsius;
  } else { // Farenheit
    state.currentTemperature = celsiusToFarenheit(celsius);
  }

  // Avoid erroneous values
  if (state.currentTemperature > 999)
    state.currentTemperature = 999;
}

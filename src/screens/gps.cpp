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


#include <screens/gps.h>
#include <display.h>
#include <memory.h>

void drawGpsLayout() {
  // Draw titles
  u8g2->setFont(u8g2_font_4x6_tr);
  u8g2->drawStr(0, 6, "Latitude:");
  u8g2->drawStr(0, 12, "Longitude:");
  u8g2->drawStr(0, 18, "Altitude:");
  u8g2->drawStr(0, 24, "Satellites:");
  u8g2->drawStr(0, 30, "Time:");
  u8g2->drawStr(0, 36, "Speed:");
  u8g2->drawStr(0, 42, "Precision:");
  u8g2->drawStr(0, 48, "Age:");
  u8g2->drawStr(0, 54, "Chars proc.:");
  u8g2->drawStr(0, 60, "Fix:");

  // Draw values
  String currentTime;

  if (state.timeHours < 10) currentTime += "0";
  currentTime += String(state.timeHours);
  currentTime += ":";

  if (state.timeMinutes < 10) currentTime += "0";
  currentTime += String(state.timeMinutes);
  currentTime += ":";

  if (state.timeSeconds < 10) currentTime += "0";
  currentTime += String(state.timeSeconds);

  u8g2->setFont(u8g2_font_4x6_tr);
  u8g2->drawStr(60, 6, String(state.currentLatitude, 6).c_str());
  u8g2->drawStr(60, 12, String(state.currentLongitude, 6).c_str());
  u8g2->drawStr(60, 18, String(state.currentAltitude).c_str());
  u8g2->drawStr(60, 24, String(state.gpsSatellites).c_str());
  u8g2->drawStr(60, 30, String(currentTime).c_str());
  u8g2->drawStr(60, 36, String(state.currentSpeed).c_str());
  u8g2->drawStr(60, 42, String(state.gpsPrecision).c_str());
  u8g2->drawStr(60, 48, String(state.gpsDataAge).c_str());
  u8g2->drawStr(60, 54, String(state.gpsCharsProcessed).c_str());
  if (state.gpsFix) {
    u8g2->drawStr(60, 60, "Yes");
  } else {
    u8g2->drawStr(60, 60, "No");
  }
}

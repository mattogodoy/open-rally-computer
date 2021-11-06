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


#include <utils.h>
#include <display.h>
#include <memory.h>
#include <language.h>
#include <release.h>

int getCenterPosition(String str) {
  return 64 - (u8g2->getStrWidth(str.c_str()) / 2) - 2;
}

void drawStrIndexRightAligned(int strIndex, int padding, int y) {
  int xPos = 128 - padding;
  xPos -= u8g2->getStrWidth(get_string(memory.config.language, strIndex));

  u8g2->drawStr(xPos, y, get_string(memory.config.language, strIndex));
}

void drawStrRightAligned(String str, int padding, int y) {
  int xPos = 128 - padding;
  xPos -= u8g2->getStrWidth(str.c_str());

  u8g2->drawStr(xPos, y, str.c_str());
}

char* secondsToTimeString(unsigned long t) { // t is time in seconds
  static char str[12];
  int h = t / 3600;
  t = t % 3600;
  int m = t / 60;
  int s = t % 60;

  // If the trip is hours long, hide the seconds. Else, hide the hours
  // if(h > 0){
  //   sprintf(str, "%02d:%02d", h, m);
  // } else {
  //   sprintf(str, "%02d:%02d", m, s);
  // }

  sprintf(str, "%02d:%02d:%02d", h, m, s);

  return str;
}

char* secondsToHHMM(unsigned long t) { // t is time in seconds
  static char str[12];
  int h = t / 3600;
  t = t % 3600;
  int m = t / 60;

  sprintf(str, "%02d:%02d", h, m);

  return str;
}

char* secondsToSS(unsigned long t) { // t is time in seconds
  static char str[12];
  t = t % 3600;
  int s = t % 60;

  sprintf(str, ":%02d", s);

  return str;
}

String getSerialNumber() {
  uint64_t chipID = ESP.getEfuseMac(); // The chip ID is essentially its MAC address (length: 6 bytes)
  unsigned long cid1 = (unsigned long)((chipID & 0xFFFF00000000) >> 32);
  unsigned long cid2 = (unsigned long)((chipID & 0x0000FFFF0000) >> 16);
  unsigned long cid3 = (unsigned long)((chipID & 0x00000000FFFF));
  return String(REL_BOARD_VERSION) + "-" + String(cid1, HEX) + String(cid2, HEX) + String(cid3, HEX);
}

float roundToOneDecimal(float value) {
  return round(value * 10) / 10.0;
}

float celsiusToFarenheit(float celsius) {
  return (celsius * 18 + 325) / 10;
}

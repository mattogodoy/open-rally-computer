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


#include <screens/status_bar.h>
#include <memory.h>
#include <display.h>
#include <language.h>
#include <buttons.h>
#include <utils.h>
#include <units.h>
#include <str_index.h>

void drawStatusBar() {
  int elapsedMillis = 0;

  // This is to avoid repeating the animation once the trip was reset
  if (state.currentScreen == SCREEN_ODOMETER && memory.config.tripPartial == 0) {
    elapsedMillis = 0;
  } else {
    elapsedMillis = millis() - state.selectButtonPressedSince;
  }

  if (state.selectButtonPressedSince == 0 || elapsedMillis < BTN_HOLD_LOAD_DELAY) {
    u8g2->drawBox(0, 0, 128, 9);
    // Invert draw color
    u8g2->setDrawColor(0);

    // -- GPS fix status
    if (state.gpsFix) {
      // u8g2->drawDisc(4, 4, 3, U8G2_DRAW_ALL);

      // -- GPS signal quality (based on HDOP)
      // Values of 100, or less indicate an ideal satellite configuration
      // Values of 100-200 are not ideal, but still excellent for most uses
      // Values of 200-500 may be good enough to use for navigation, but this may depend on other factors
      // Values above 500 are not really good enough for our purposes
      u8g2->drawBox(1, 7, 2, 1);
      if (state.gpsFix && state.gpsPrecision < 500) u8g2->drawBox(4, 5, 2, 3);
      if (state.gpsFix && state.gpsPrecision < 200) u8g2->drawBox(7, 3, 2, 5);
      if (state.gpsFix && state.gpsPrecision < 100) u8g2->drawBox(10, 1, 2, 7);
    } else {
      u8g2->drawCircle(6, 4, 3, U8G2_DRAW_ALL);

      // Make the circle spin (only if receiving data from GPS)
      switch (state.gpsDiscPos) {
        case 0:
          u8g2->drawDisc(6, 4, 3, U8G2_DRAW_UPPER_RIGHT);
          break;
        case 1:
          u8g2->drawDisc(6, 4, 3, U8G2_DRAW_LOWER_RIGHT);
          break;
        case 2:
          u8g2->drawDisc(6, 4, 3, U8G2_DRAW_LOWER_LEFT);
          break;
        case 3:
          u8g2->drawDisc(6, 4, 3, U8G2_DRAW_UPPER_LEFT);
          break;
      }
    }


    // -- GPS satellites icon
    u8g2->drawHLine(109, 4, 3);
    u8g2->drawHLine(111, 3, 3);
    u8g2->drawHLine(113, 4, 3);
    u8g2->drawHLine(111, 5, 3);

    // -- GPS satellites number
    u8g2->setFont(u8g2_font_blipfest_07_tn);
    u8g2->drawStr(118, 7, String(state.gpsSatellites).c_str());


    // -- Time
    String currentTime;

    if (state.timeHours < 10) currentTime += "0";
    currentTime += String(state.timeHours);
    currentTime += ":";

    if (state.timeMinutes < 10) currentTime += "0";
    currentTime += String(state.timeMinutes);

    u8g2->setFont(u8g2_font_torussansbold8_8r);
    u8g2->drawStr(44, 8, currentTime.c_str());


    // -- Temperature
    /* ===== Temperature not working correctly =====
    String currentTemperature;

    if(memory.config.units == UNITS_METRIC){
      currentTemperature = String(state.currentTemperature) + "-C"; // The "-" is a trick to get the perfect space for the "º"
    } else {
      currentTemperature = String(state.currentTemperature) + "-F";
    }

    u8g2->setFont(u8g2_font_blipfest_07_tr);
    drawStrRightAligned(currentTemperature.c_str(), 1, 7);
    u8g2->drawFrame(120, 2, 3, 3); // Degree symbol (the one in the font sucks)
    ================================================ */

    // Return draw color to normality
    u8g2->setDrawColor(1);
  } else {
    int loadingStr;
    switch (state.currentScreen) {
      case SCREEN_ODOMETER:
        loadingStr = STR_RESET_DISTANCE;
        break;
      case SCREEN_SPEED:
      case SCREEN_TIME:
      case SCREEN_HEADING:
        loadingStr = STR_CONFIGURATION;
        break;
      default:
        loadingStr = STR_CONFIGURATION;
    }

    u8g2->setFontMode(1); // activate transparent font mode
    u8g2->setDrawColor(1);
    int barWidth = (elapsedMillis - BTN_HOLD_LOAD_DELAY) * 100 / (BTN_HOLD_DELAY - (BTN_HOLD_LOAD_DELAY * 2));
    u8g2->drawBox(0, 0, barWidth, 9);
    u8g2->setFont(u8g2_font_torussansbold8_8r);
    u8g2->setDrawColor(2);
    u8g2->drawStr(getCenterPosition(get_string(memory.config.language, loadingStr)), 8, get_string(memory.config.language, loadingStr));
    u8g2->setDrawColor(1);
  }
}
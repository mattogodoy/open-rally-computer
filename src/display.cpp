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


#include <display.h>
#include <screens/splash.h>
#include <screens/odometer.h>
#include <screens/speed.h>
#include <screens/time.h>
#include <screens/heading.h>
#include <screens/settings.h>
#include <screens/input.h>
#include <screens/language.h>
#include <screens/gps.h>
#include <screens/update.h>
#include <pins.h>
#include <memory.h>

// Initialize display
U8G2_UC1701_MINI12864_F_4W_SW_SPI* u8g2 = new U8G2_UC1701_MINI12864_F_4W_SW_SPI(U8G2_R0,
  PIN_DISPLAY_CLOCK, PIN_DISPLAY_DATA, PIN_DISPLAY_CS, PIN_DISPLAY_DC, PIN_DISPLAY_RESET);

void initializeDisplay() {
  initDisplayRotation();
  initBacklight();

  u8g2->begin(PIN_BUTTON_SELECT, PIN_BUTTON_PREV, PIN_BUTTON_NEXT);
  u8g2->setContrast(220);
}

void drawSplashScreen() {
  u8g2->clearBuffer();
  drawScreen(SCREEN_SPLASH);
  u8g2->sendBuffer();
}

void drawScreen(int index) {
  switch (index) {
    case SCREEN_SPLASH:
      drawSplashLayout();
      break;
    case SCREEN_ODOMETER:
      drawOdometerLayout();
      break;
    case SCREEN_SPEED:
      drawSpeedLayout();
      break;
    case SCREEN_TIME:
      drawTimeLayout();
      break;
    case SCREEN_HEADING:
      drawHeadingLayout();
      break;
    case SCREEN_MENU:
      drawSettingsLayout();
      break;
    case SCREEN_INPUT:
      drawInputLayout();
      break;
    case SCREEN_LANGUAGE:
      drawLanguageLayout();
      break;
    case SCREEN_GPS:
      drawGpsLayout();
      break;
    case SCREEN_UPDATE:
      drawUpdateLayout();
      break;
    default:
      drawOdometerLayout();
      break;
  }
}

void initBacklight() {
  ledcSetup(0, 10000, 8); // LED channel, frequency, resolution
  ledcAttachPin(PIN_BACKLIGHT, 0);

  setBacklight(memory.config.backlight);
}

void initDisplayRotation() {
  if (memory.config.flipScreen) {
    u8g2->setDisplayRotation(U8G2_R2); // 180 degrees clockwise rotation
  } else {
    u8g2->setDisplayRotation(U8G2_R0); // No rotation, landscape
  }
}

void setBacklight(int value) {
  int dutyCycle = map(value, 0, 10, 0, 255); // Map values from 0-10 to 0-255

  // Prevent overshoot
  if (dutyCycle > 255)
    dutyCycle = 255;

  ledcWrite(0, dutyCycle); // Channel, duty cycle
}

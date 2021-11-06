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


#include <screens/settings.h>
#include <display.h>
#include <language.h>
#include <memory.h>
#include <menu.h>
#include <str_index.h>

void drawSettingsLayout() {
  u8g2->setFont(u8g2_font_6x12_tr);

  const char* menu_items = get_menu_items(memory.config.language, MENU_LIST_SETTINGS);
  const char* menu_title = get_string(memory.config.language, STR_CONFIGURATION);
  int tmp_result = 0;

  state.menuCurrentSelection = u8g2->userInterfaceSelectionList(
    menu_title,
    state.menuCurrentSelection,
    menu_items);

  if (state.menuCurrentSelection == 0)
    return;

  switch (state.menuCurrentSelection) {
    case MENU_RESET:
      state.menuCurrentValue = u8g2->userInterfaceMessage(
        get_string(memory.config.language, STR_RESET), // Title 1
        get_string(memory.config.language, STR_RESET_TRIP), // Title 2
        get_string(memory.config.language, STR_SURE), // Title 3
        get_string(memory.config.language, STR_SURE_BUTTONS)); // Buttons (divided by \n)

      if (state.menuCurrentValue == 2) {
        resetTripValues();

        // Back to the main screen
        state.currentScreen = SCREEN_ODOMETER;
      }
      break;

    case MENU_LANGUAGE:
      state.currentScreen = SCREEN_LANGUAGE;
      break;

    case MENU_PRECISION:
      state.menuCurrentValue = u8g2->userInterfaceMessage(
        get_string(memory.config.language, STR_PRECISION), // Title 1
        get_string(memory.config.language, STR_PRECISION_TITLE1), // Title 2
        get_string(memory.config.language, STR_PRECISION_TITLE2), // Title 3
        get_string(memory.config.language, STR_PRECISION_OPTIONS)); // Buttons (divided by \n)

      if (state.menuCurrentValue > 0) {
        memory.config.precision = state.menuCurrentValue;
        saveConfig();

        // Back to the main screen
        state.currentScreen = SCREEN_ODOMETER;
      }
      break;

    case MENU_UNITS:
      state.units = u8g2->userInterfaceMessage(
        get_string(memory.config.language, STR_UNITS_SYSTEM), // Title 1
        get_string(memory.config.language, STR_UNITS_METRIC_DEF), // Title 2
        get_string(memory.config.language, STR_UNITS_IMPERIAL_DEF), // Title 3
        get_string(memory.config.language, STR_UNITS_BUTTONS)); // Buttons (divided by \n)

      if (state.units != memory.config.units) {
        memory.config.units = state.units;
        saveConfig();
        resetTripValues(); // To avoid weird distance and average numbers

        // Back to the main screen
        state.currentScreen = SCREEN_ODOMETER;
      }
      break;

    case MENU_TIMEZONE:
      state.currentScreen = SCREEN_INPUT;
      break;

    case MENU_BACKLIGHT:
      state.currentScreen = SCREEN_INPUT;
      break;

    case MENU_QUICKVIEW:
      tmp_result = u8g2->userInterfaceMessage(
        get_string(memory.config.language, STR_QUICKVIEW), // Title 1
        get_string(memory.config.language, STR_QUICKVIEW_TITLE1), // Title 2
        get_string(memory.config.language, STR_QUICKVIEW_TITLE2), // Title 3
        get_string(memory.config.language, STR_SURE_BUTTONS)); // Buttons (divided by \n)

      if (tmp_result == 1) {
        memory.config.quickViewEnabled = false;
        saveConfig();

        state.currentScreen = SCREEN_ODOMETER; // Back to the main screen
      } else if (tmp_result == 2) {
        memory.config.quickViewEnabled = true;
        saveConfig();

        state.currentScreen = SCREEN_ODOMETER; // Back to the main screen
      }
      break;

    case MENU_FLIP_SCREEN:
      tmp_result = u8g2->userInterfaceMessage(
        get_string(memory.config.language, STR_FLIP_SCREEN), // Title 1
        get_string(memory.config.language, STR_FLIP_SCREEN_TITLE1), // Title 2
        get_string(memory.config.language, STR_FLIP_SCREEN_TITLE2), // Title 3
        get_string(memory.config.language, STR_SURE_BUTTONS)); // Buttons (divided by \n)

      if (tmp_result == 1) {
        memory.config.flipScreen = false;
        u8g2->setDisplayRotation(U8G2_R0); // No rotation, landscape
        saveConfig();

        state.currentScreen = SCREEN_ODOMETER; // Back to the main screen
      } else if (tmp_result == 2) {
        memory.config.flipScreen = true;
        u8g2->setDisplayRotation(U8G2_R2); // 180 degrees clockwise rotation
        saveConfig();

        state.currentScreen = SCREEN_ODOMETER; // Back to the main screen
      }
      break;

    case MENU_GPS:
      state.currentScreen = SCREEN_GPS;
      break;

    case MENU_UPDATE:
      state.currentScreen = SCREEN_UPDATE;
      break;

    case MENU_VERSION:
      state.currentScreen = SCREEN_SPLASH;
      break;

    case MENU_FACTORY:
      state.menuCurrentValue = u8g2->userInterfaceMessage(
        get_string(memory.config.language, STR_FACTORY), // Title 1
        get_string(memory.config.language, STR_FACTORY_TITLE1), // Title 2
        get_string(memory.config.language, STR_SURE), // Title 3
        get_string(memory.config.language, STR_SURE_BUTTONS)); // Buttons (divided by \n)

      if (state.menuCurrentValue == 2) {
        resetConfig(); // Reset all values to factory defaults

        // Back to the main screen
        state.currentScreen = SCREEN_ODOMETER;
      }
      break;
  }
}

void resetTripValues() {
  memory.config.tripTotal = 0;
  memory.config.tripPartial = 0;
  memory.config.tripTime = 0;
  memory.config.maxSpeed = 0;
  memory.config.avgAccumulator = 0;
  memory.config.avgSamples = 0;
  state.average = 0;

  saveConfig();
}

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


#include <screens/input.h>
#include <memory.h>
#include <menu.h>
#include <str_index.h>
#include <display.h>
#include <gps.h>
#include <language.h>
#include <constants.h>

void drawInputLayout() {
  int margin, width, title, post_text, min, max;

  switch (state.menuCurrentSelection) {
    case MENU_TIMEZONE:
      title = STR_TIMEZONE;
      post_text = STR_TIMEZONE_UTC;
      min = TIMEZONE_MIN;
      max = TIMEZONE_MAX;
      if (state.inputValue == -99)
        state.inputValue = memory.config.timeZone;
      break;

    case MENU_BACKLIGHT:
      title = STR_BACKLIGHT;
      post_text = STR_BACKLIGHT_POST;
      min = BACKLIGHT_MIN;
      max = BACKLIGHT_MAX;
      if (state.inputValue == -99)
        state.inputValue = memory.config.backlight;
      break;

    default:
      title = STR_NO;
      post_text = STR_NO;
      min = 0;
      max = 0;
  }

  if (state.inputValue > max) {
    state.inputValue = max;
  } else if (state.inputValue < min) {
    state.inputValue = min;
  }

  // Draw banner and title
  u8g2->drawBox(0, 0, DISPLAY_WIDTH, 14);
  u8g2->setDrawColor(0);
  u8g2->setFont(u8g2_font_6x12_tr);
  width = u8g2->getStrWidth(get_string(memory.config.language, title));
  margin = (DISPLAY_WIDTH / 2) - (width / 2);
  u8g2->drawStr(margin, 10, get_string(memory.config.language, title));

  // Draw big number
  u8g2->setDrawColor(1);
  u8g2->setFont(u8g2_font_profont22_mn);
  char buffer[10];
  sprintf(buffer, "%d", state.inputValue);
  width = u8g2->getStrWidth(buffer);
  margin = (DISPLAY_WIDTH / 2) - (width / 2);
  u8g2->drawStr(margin, 40, buffer);

  // Draw post text
  u8g2->setFont(u8g2_font_6x12_tr);
  width = u8g2->getStrWidth(get_string(memory.config.language, post_text));
  margin = (DISPLAY_WIDTH / 2) - (width / 2);
  u8g2->drawStr(margin, 60, get_string(memory.config.language, post_text));
}

void saveInputValue() {
  switch (state.menuCurrentSelection) {
    case MENU_TIMEZONE:
      memory.config.timeZone = state.inputValue;
      adjustTimeZone();
      saveConfig();
      state.inputValue = -99;
      state.currentScreen = SCREEN_MENU;
      break;

    case MENU_BACKLIGHT:
      memory.config.backlight = state.inputValue;
      setBacklight(state.inputValue);
      saveConfig();
      state.inputValue = -99;
      state.currentScreen = SCREEN_MENU;
      break;

    default:
      break;
  }
}

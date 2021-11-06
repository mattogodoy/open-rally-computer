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


#include <screens/language.h>
#include <display.h>
#include <language.h>
#include <menu.h>
#include <str_index.h>
#include <memory.h>


void drawLanguageLayout() {
  u8g2->setFont(u8g2_font_6x12_tr);

  const char* menu_items = get_menu_items(memory.config.language, MENU_LIST_LANGUAGES);
  const char* menu_title = get_string(memory.config.language, STR_LANGUAGE);

  // Show languages menu
  state.menuCurrentLanguage = u8g2->userInterfaceSelectionList(
    menu_title,
    memory.config.language,
    menu_items);

  if (state.menuCurrentLanguage == 0) {
    return; // Long press, cancel
  } else {
    saveSelectedLanguage();
  }
}

void saveSelectedLanguage() {
  memory.config.language = state.menuCurrentLanguage;
  saveConfig();
  state.currentScreen = SCREEN_MENU;
}

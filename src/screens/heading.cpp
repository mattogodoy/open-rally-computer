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


#include <screens/heading.h>
#include <screens/status_bar.h>
#include <Arduino.h>
#include <display.h>
#include <utils.h>
#include <str_index.h>
#include <memory.h>
#include <language.h>

void drawHeadingLayout() {
  String heading = String(state.currentHeading);

  // Draw status bar
  drawStatusBar();

  // Draw title
  u8g2->setFont(u8g2_font_7x13B_mr);
  u8g2->drawStr(0, 21, get_string(memory.config.language, STR_HEADING));

  // Draw heading
  u8g2->setFont(u8g2_font_logisoso38_tn);
  u8g2->drawStr(getCenterPosition(heading.c_str()), 63, heading.c_str());
  int degXpos = getCenterPosition(heading.c_str()) + u8g2->getStrWidth(heading.c_str()) + 8;
  u8g2->drawDisc(degXpos, 28, 3, U8G2_DRAW_ALL); // Degree symbol (the one in the font sucks)
  u8g2->setDrawColor(0);
  u8g2->drawDisc(degXpos, 28, 1, U8G2_DRAW_ALL);
  u8g2->setDrawColor(1);
}

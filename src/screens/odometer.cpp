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


#include <screens/odometer.h>
#include <screens/status_bar.h>
#include <Arduino.h>
#include <display.h>
#include <utils.h>
#include <str_index.h>
#include <memory.h>
#include <language.h>

void drawOdometerLayout() {
  String partial = String(memory.config.tripPartial);
  String total = String(memory.config.tripTotal);
  String heading = String(state.currentHeading);

  if (memory.config.precision == 1) {
    // Remove last digit
    partial.remove(partial.length() - 1);
    total.remove(total.length() - 1);
  }

  // Draw status bar
  drawStatusBar();

  // Draw title
  u8g2->setFont(u8g2_font_logisoso16_tf);
  u8g2->drawStr(0, 28, total.c_str());

  // Draw heading
  u8g2->setFont(u8g2_font_logisoso16_tf);
  drawStrRightAligned(heading, 5, 28);
  u8g2->drawFrame(125, 12, 3, 3); // Degree symbol (the one in the font sucks)

  // Draw distance
  u8g2->setFont(u8g2_font_logisoso32_tn);
  u8g2->drawStr(getCenterPosition(partial.c_str()), 63, partial.c_str());
}

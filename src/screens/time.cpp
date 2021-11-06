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


#include <screens/time.h>
#include <screens/status_bar.h>
#include <Arduino.h>
#include <display.h>
#include <utils.h>
#include <str_index.h>
#include <memory.h>
#include <language.h>

void drawTimeLayout() {
  String tripTimeHHMM = secondsToHHMM(memory.config.tripTime);
  String tripTimeSS = secondsToSS(memory.config.tripTime);

  // Draw status bar
  drawStatusBar();

  // Draw title
  u8g2->setFont(u8g2_font_7x13B_mr);
  u8g2->drawStr(0, 21, get_string(memory.config.language, STR_TRIP_TIME));

  // Draw Hours and Minutes
  u8g2->setFont(u8g2_font_logisoso32_tn);
  u8g2->drawStr(4, 63, tripTimeHHMM.c_str());

  // Draw Seconds
  u8g2->setFont(u8g2_font_logisoso16_tf);
  u8g2->drawStr(98, 63, tripTimeSS.c_str());
}

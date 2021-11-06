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


#include <screens/speed.h>
#include <screens/status_bar.h>
#include <Arduino.h>
#include <display.h>
#include <utils.h>
#include <str_index.h>
#include <units.h>
#include <memory.h>
#include <language.h>

void drawSpeedLayout() {
  String currentSpeed = String(state.currentSpeed);
  String avgSpeed = String(state.average);
  String maxSpeed = String(memory.config.maxSpeed);

  // Draw status bar
  drawStatusBar();

  // Draw drawLayout
  u8g2->drawVLine(78, 9, 55);
  u8g2->drawHLine(79, 37, 53);

  // Draw titles
  u8g2->setFont(u8g2_font_7x13B_mr);
  u8g2->drawStr(0, 21, get_string(memory.config.language, STR_SPEED));
  u8g2->setFont(u8g2_font_4x6_tr);
  u8g2->drawStr(81, 16, get_string(memory.config.language, STR_AVERAGE));
  u8g2->drawStr(81, 45, get_string(memory.config.language, STR_MAX_SPEED));

  // Draw labels
  if (memory.config.units == UNITS_METRIC) {
    drawStrIndexRightAligned(STR_KM_H, 0, 34);
    drawStrIndexRightAligned(STR_KM_H, 0, 64);
  } else {
    drawStrIndexRightAligned(STR_MI_H, 0, 34);
    drawStrIndexRightAligned(STR_MI_H, 0, 64);
  }

  // Draw average
  u8g2->setFont(u8g2_font_logisoso16_tf);
  drawStrRightAligned(avgSpeed, 17, 34);
  // Draw max
  drawStrRightAligned(maxSpeed, 17, 64);

  // Draw speed
  u8g2->setFont(u8g2_font_logisoso38_tn);
  u8g2->drawStr(0, 63, currentSpeed.c_str());
}

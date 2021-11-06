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


#include <screens/splash.h>
#include <display.h>
#include <release.h>
#include <utils.h>

void drawSplashLayout() {
  // ==========================================
  // I use string literals because during setup
  // the Definitions.h file is not loaded yet
  // ==========================================

  // Draw Serial Number
  String sn = String("S/N: ") + getSerialNumber();
  u8g2->setFont(u8g2_font_4x6_tr);
  u8g2->drawStr(0, 6, sn.c_str());

  // Draw brand
  u8g2->setFont(u8g2_font_profont29_tf);
  u8g2->drawStr(getCenterPosition("ORC") + 2, 40, "ORC");

  // Draw version
  String version = String("v") + REL_VERSION + String(" (build ") + REL_BUILD + String(")");
  u8g2->setFont(u8g2_font_lucasfont_alternate_tr);
  u8g2->drawStr(0, 64, version.c_str());
}

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


#pragma once

#include <Button.h>

#define BTN_HOLD_DELAY        1000
#define BTN_HOLD_LOAD_DELAY   200
#define BTN_HOLD_SKIP_DELAY   300
#define BTN_HOLD_REPEAT       100

void onButtonSelectRelease(Button& btn, uint16_t duration);
void onButtonSelectPress(Button& btn);
void onButtonSelectHold(Button& btn, uint16_t duration);
void onButtonNextPress(Button& btn);
void onButtonNextHold(Button& btn, uint16_t duration, uint16_t repeatCount);
void onButtonNextRelease(Button& btn, uint16_t duration);
void onButtonPrevPress(Button& btn);
void onButtonPrevHold(Button& btn, uint16_t duration, uint16_t repeatCount);
void onButtonPrevRelease(Button& btn, uint16_t duration);
void initButtons();
void checkButtons();
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

#include <Arduino.h>

#define UPDATE_START          1
#define UPDATE_CONNECTING     2
#define UPDATE_CHECKING       3
#define UPDATE_DOWNLOADING    4
#define UPDATE_UPGRADING      5
#define UPDATE_CONN_ERROR     6
#define UPDATE_UPGR_ERROR     7
#define UPDATE_FINISHED       8
#define UPDATE_TIMEOUT        60000 // 60 seconds

String getHeaderValue(String header, String headerName);
void updateScreen();
void connectToWiFi();
void checkLatestVersion();
void execOTA();

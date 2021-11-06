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


#include <screens/update.h>
#include <memory.h>
#include <ota.h>
#include <display.h>

void drawUpdateLayout() {
  switch (state.currentUpdateStep) {
    case UPDATE_START:
      drawStepInstructions();
      break;
    case UPDATE_CONNECTING:
      drawStepConnecting();
      break;
    case UPDATE_CHECKING:
      drawStepConnecting();
      break;
    case UPDATE_DOWNLOADING:
      drawStepDownloading();
      break;
    case UPDATE_UPGRADING:
      drawStepUpgrading();
      break;
    case UPDATE_CONN_ERROR:
      drawConnectionFailed();
      break;
    case UPDATE_UPGR_ERROR:
      drawUpgradeFailed();
      break;
    case UPDATE_FINISHED:
      drawUpToDate();
      break;
    default:
      drawStepInstructions();
  }
}

void drawStepInstructions() {
  u8g2->setFont(u8g2_font_4x6_tr);
  u8g2->drawStr(0, 6, "FIRMWARE UPDATE:");
  u8g2->drawStr(0, 20, "Create a WiFi hotspot with:");
  u8g2->drawStr(0, 28, "Name: OpenRally");
  u8g2->drawStr(0, 36, "Password: updateorc");
  u8g2->drawStr(0, 48, "Press the Select button when");
  u8g2->drawStr(0, 56, "ready...");
}

void drawStepConnecting() {
  u8g2->drawStr(0, 6, "Connecting to WiFi");
  u8g2->drawStr(0, 14, "Please wait...");
}

void drawStepChecking() {
  u8g2->drawStr(0, 6, "CONNECTED!");
  u8g2->drawStr(0, 14, "Checking for newer versions...");
}

void drawStepDownloading() {
  u8g2->drawStr(0, 6, "UPDATE AVAILABLE");
  u8g2->drawStr(0, 14, "Downloading...");
}

void drawStepUpgrading() {
  u8g2->drawStr(0, 6, "UPGRADING FIRMWARE");
  u8g2->drawStr(0, 14, "This may take 2 - 5 minutes to");
  u8g2->drawStr(0, 22, "complete. Please be patient...");
  u8g2->drawStr(0, 35, "DO NOT TURN THE DEVICE OFF");
}

void drawConnectionFailed() {
  u8g2->drawStr(0, 6, "CONNECTION FAILED");
  u8g2->drawStr(0, 14, "Please check your WiFi spot");
  u8g2->drawStr(0, 22, "configuration and try again.");
  state.updatingFirmware = 0;
}

void drawUpgradeFailed() {
  u8g2->drawStr(0, 6, "UPGRADE FAILED");
  u8g2->drawStr(0, 14, "There was an error while trying");
  u8g2->drawStr(0, 22, "to download the upgrade file.");
  u8g2->drawStr(0, 38, "Please try again later.");
  state.updatingFirmware = 0;
}

void drawUpToDate() {
  u8g2->drawStr(0, 6, "UP TO DATE");
  u8g2->drawStr(0, 14, "You have the latest version.");
  state.updatingFirmware = 0;
}
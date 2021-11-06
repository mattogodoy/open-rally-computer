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


#include <buttons.h>
#include <screens/input.h>
#include <ButtonEventCallback.h>
#include <PushButton.h>
#include <Bounce2.h>
#include <U8g2lib.h>
#include <pins.h>
#include <memory.h>
#include <screens.h>
#include <ota.h>
#include <menu.h>
#include <display.h>

PushButton button_select = PushButton(PIN_BUTTON_SELECT, ENABLE_INTERNAL_PULLUP);
PushButton button_next = PushButton(PIN_BUTTON_NEXT, ENABLE_INTERNAL_PULLUP);
PushButton button_prev = PushButton(PIN_BUTTON_PREV, ENABLE_INTERNAL_PULLUP);
int holdMultiplier = 1;

// This replaces the UI buttons functionality on u8g2 with mine
// Otherwise, I can't read button inputs while on the settings screen
uint8_t u8x8_GetMenuEvent(u8x8_t* u8x8) {
  checkButtons();

  int cmd = state.menuLastCommand;
  state.menuLastCommand = 0;

  return cmd;
}

void onButtonSelectRelease(Button& btn, uint16_t duration) {
  state.selectButtonPressedSince = 0;

  // This avoids calling this callback when releasing
  // the center button after a Hold event
  if (duration >= BTN_HOLD_SKIP_DELAY)
    return void();

  switch (state.currentScreen) {
    case SCREEN_ODOMETER:
      state.currentScreen = SCREEN_SPEED;
      break;
    case SCREEN_SPEED:
      state.currentScreen = SCREEN_TIME;
      break;
    case SCREEN_TIME:
      state.currentScreen = SCREEN_HEADING;
      break;
    case SCREEN_HEADING:
      state.currentScreen = SCREEN_ODOMETER;
      break;
    case SCREEN_MENU:
      state.menuLastCommand = U8X8_MSG_GPIO_MENU_SELECT;
      break;
    case SCREEN_INPUT:
      saveInputValue();
      break;
    case SCREEN_LANGUAGE:
      state.menuLastCommand = U8X8_MSG_GPIO_MENU_SELECT;
      break;
    case SCREEN_UPDATE:
      if (state.updatingFirmware == 1)
        return void();

      switch (state.currentUpdateStep) {
        case UPDATE_START:
          checkLatestVersion();
          break;
        case UPDATE_CONN_ERROR:
        case UPDATE_UPGR_ERROR:
        case UPDATE_FINISHED:
          state.currentUpdateStep = UPDATE_START;

          // Go back to menu
          state.currentScreen = SCREEN_MENU;
          break;

        default:
          checkLatestVersion();
          break;
      }
      break;
    case SCREEN_SPLASH:
      // Go back to menu
      state.currentScreen = SCREEN_MENU;
      break;
  }
}

void onButtonSelectPress(Button& btn) {
  switch (state.currentScreen) {
    case SCREEN_ODOMETER:
    case SCREEN_SPEED:
    case SCREEN_TIME:
    case SCREEN_HEADING:
      state.selectButtonPressedSince = millis();
      break;
  }
}


void onButtonSelectHold(Button& btn, uint16_t duration) {
  switch (state.currentScreen) {
    case SCREEN_ODOMETER:
      memory.config.tripPartial = 0;
      state.alreadySaved = false; // Indicate that changes has been made
      break;
    case SCREEN_SPEED:
      state.currentScreen = SCREEN_MENU;
      break;
    case SCREEN_TIME:
      state.currentScreen = SCREEN_MENU;
      break;
    case SCREEN_HEADING:
      state.currentScreen = SCREEN_MENU;
      break;
    case SCREEN_MENU:
      state.currentScreen = SCREEN_ODOMETER;
      state.menuLastCommand = U8X8_MSG_GPIO_MENU_HOME;
      break;
    case SCREEN_INPUT:
      state.currentScreen = SCREEN_MENU;
      state.inputValue = 0;
      break;
    case SCREEN_LANGUAGE:
      state.menuLastCommand = U8X8_MSG_GPIO_MENU_HOME;
      state.currentScreen = SCREEN_MENU;
      break;
    case SCREEN_GPS:
      state.currentScreen = SCREEN_ODOMETER;
      state.menuLastCommand = U8X8_MSG_GPIO_MENU_HOME;
      break;
    case SCREEN_UPDATE:
      if (state.updatingFirmware == 1)
        return;

      state.menuLastCommand = U8X8_MSG_GPIO_MENU_HOME;
      state.currentScreen = SCREEN_MENU;
      break;
  }
}


void onButtonNextPress(Button& btn) {
  switch (state.currentScreen) {
    case SCREEN_ODOMETER:
      // Only change the distance if we are not in QuickView
      if (state.quickViewScreen == 0 && millis() > 3000) { // The second condition prevents a glitch on boot
        if (memory.config.precision == 1) {
          memory.config.tripPartial += 0.1 * holdMultiplier;
        } else {
          memory.config.tripPartial += 0.01 * holdMultiplier;
        }
      }
      break;
    case SCREEN_SPEED:
    case SCREEN_TIME:
    case SCREEN_HEADING:
      // QuickView function for these screens
      if (memory.config.quickViewEnabled) {
        state.quickViewScreen = state.currentScreen;
        state.currentScreen = SCREEN_ODOMETER;
      }
      break;
    case SCREEN_MENU:
      state.menuLastCommand = U8X8_MSG_GPIO_MENU_PREV; // Weird error switches Next with Prev
      break;
    case SCREEN_INPUT:
      state.inputValue++;
      if (state.menuCurrentSelection == MENU_BACKLIGHT)
        setBacklight(state.inputValue);
      break;
    case SCREEN_LANGUAGE:
      state.menuLastCommand = U8X8_MSG_GPIO_MENU_PREV; // Weird error switches Next with Prev
      break;
  }
}


void onButtonNextHold(Button& btn, uint16_t duration, uint16_t repeatCount) {
  if (duration > 5000) holdMultiplier = 5;
  if (duration > 10000) holdMultiplier = 10;

  onButtonNextPress(btn);
}


void onButtonNextRelease(Button& btn, uint16_t duration) {
  holdMultiplier = 1; // Restore multiplier to 1
  state.alreadySaved = false; // Indicate that changes has been made

  // QuickView function
  if (state.quickViewScreen != 0 && state.currentScreen == SCREEN_ODOMETER) {
    state.currentScreen = state.quickViewScreen;
    state.quickViewScreen = 0; // Reset the quickView so it does not work when you are in the Odometer screen
  }
}


void onButtonPrevPress(Button& btn) {
  switch (state.currentScreen) {
    case SCREEN_ODOMETER:
      // Only change the distance if we are not in QuickView
      if (state.quickViewScreen == 0 && millis() > 3000) { // The second condition prevents a glitch on boot
        if (memory.config.precision == 1) {
          memory.config.tripPartial -= 0.1 * holdMultiplier;
        } else {
          memory.config.tripPartial -= 0.01 * holdMultiplier;
        }
        if (memory.config.tripPartial < 0) memory.config.tripPartial = 0;
      }
      break;
    case SCREEN_SPEED:
    case SCREEN_TIME:
    case SCREEN_HEADING:
      // QuickView function for these screens
      if (memory.config.quickViewEnabled) {
        state.quickViewScreen = state.currentScreen;
        state.currentScreen = SCREEN_ODOMETER;
      }
      break;
    case SCREEN_MENU:
      state.menuLastCommand = U8X8_MSG_GPIO_MENU_NEXT;
      break;
    case SCREEN_INPUT:
      state.inputValue--;
      if (state.menuCurrentSelection == MENU_BACKLIGHT) {
        if (state.inputValue < 0) state.inputValue = 0;
        setBacklight(state.inputValue);
      }
      break;
    case SCREEN_LANGUAGE:
      state.menuLastCommand = U8X8_MSG_GPIO_MENU_NEXT;
      break;
  }
}


void onButtonPrevHold(Button& btn, uint16_t duration, uint16_t repeatCount) {
  if (duration > 5000) holdMultiplier = 5;
  if (duration > 10000) holdMultiplier = 10;

  onButtonPrevPress(btn);
}


void onButtonPrevRelease(Button& btn, uint16_t duration) {
  holdMultiplier = 1; // Restore multiplier to 1
  state.alreadySaved = false; // Indicate that changes has been made

  // QuickView function
  if (state.quickViewScreen != 0 && state.currentScreen == SCREEN_ODOMETER) {
    state.currentScreen = state.quickViewScreen;
    state.quickViewScreen = 0; // Reset the quickView so it does not work when you are in the Odometer screen
  }
}


void initButtons() {
  pinMode(PIN_BUTTON_PREV, INPUT_PULLUP);
  pinMode(PIN_BUTTON_SELECT, INPUT_PULLUP);
  pinMode(PIN_BUTTON_NEXT, INPUT_PULLUP); // This will not work. This pin does not have integrated pullup (https://github.com/espressif/arduino-esp32/issues/316)

  button_select.onPress(onButtonSelectPress);
  button_select.onRelease(onButtonSelectRelease);
  button_select.onHold(BTN_HOLD_DELAY, onButtonSelectHold);

  button_next.onPress(onButtonNextPress);
  button_next.onHoldRepeat(BTN_HOLD_DELAY, BTN_HOLD_REPEAT, onButtonNextHold);
  button_next.onRelease(onButtonNextRelease);

  button_prev.onPress(onButtonPrevPress);
  button_prev.onHoldRepeat(BTN_HOLD_DELAY, BTN_HOLD_REPEAT, onButtonPrevHold);
  button_prev.onRelease(onButtonPrevRelease);
}


void checkButtons() {
  button_select.update();
  button_next.update();
  button_prev.update();
}

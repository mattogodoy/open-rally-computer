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


#include <language.h>
#include <languages.h>
#include <menu.h>

const char english[][36] = {
  "Trip A",
  "Trip B",
  "Temp",
  "CAP Heading",
  "Speed",
  "Average",
  "SETTINGS",
  "Display",
  "Circumference",
  "Language",
  "Version",
  "Reset trip",
  "Dist., avg. and time",
  "Are you sure?",
  " No \n Yes ",
  "Milimeters",
  "UNITS SYSTEM",
  " Metric \n Imperial ",
  "Metric: Km/h, mm",
  "Imperial: mph, in",
  " OK ",
  "Yes",
  "No",
  "-",
  "SELECT DATA",
  "Display Backlight",
  "From 0 to 10",
  "Altitude",
  "Max speed",
  "Trip time",
  "Precision",
  "Number of decimals",
  "used for distances",
  " One \n Two ",
  "Factory defaults",
  "Restore ALL values",
  "km/h",
  "mi/h",
  "RESET",
  "ORC",
  "-",
  "QUICKVIEW",
  "Quick view of the Odo",
  "from other screens",
  "Time Zone",
  "UTC (from -12 to +14)",
  "FLIP SCREEN",
  "Flip the screen",
  "180 degrees"
};

const char spanish[][36] = {
  "Trayecto A",
  "Trayecto B",
  "Temp",
  "Rumbo CAP",
  "Velocidad",
  "Promedio",
  "CONFIGURACION",
  "Pantalla",
  "Circunferencia",
  "Idioma",
  "Version",
  "Resetear viaje",
  "Dist., prom. y tiempo",
  "Esta seguro?",
  " No \n Si ",
  "Milimetros",
  "SISTEMA DE UNIDADES",
  " Metrico \n Imperial ",
  "Metrico: Km/h, mm",
  "Imperial: mph, in",
  " OK ",
  "Si",
  "No",
  "-",
  "SELECCIONE DATO",
  "Luz de Pantalla",
  "De 0 a 10",
  "Altitud",
  "Vel. max.",
  "Tiempo de trayecto",
  "Precision",
  "Numero de decimales",
  "usado en distancias",
  " Uno \n Dos ",
  "Valores de fabrica",
  "Restaurar TODOS",
  "km/h",
  "mi/h",
  "RESETEAR",
  "ORC",
  "-",
  "QUICKVIEW",
  "Vista rapida del Odo",
  "desde otras pantallas",
  "Zona Horaria",
  "UTC (de -12 a +14)",
  "INVERTIR PANTALLA",
  "Invertir la pantalla",
  "180 grados"
};

const char* english_menu_items =
"Reset trip\n"
"Language\n"
"Precision\n"
"Units\n"
"Time zone\n"
"Display backlight\n"
"QuickView\n"
"Flip screen\n"
"GPS data\n"
"Update firmware\n"
"Version\n"
"Factory defaults";

const char* spanish_menu_items =
"Resetear viaje\n"
"Idioma\n"
"Precision\n"
"Unidades\n"
"Zona horaria\n"
"Luz de pantalla\n"
"QuickView\n"
"Invertir pantalla\n"
"Datos de GPS\n"
"Actualizar firmware\n"
"Version\n"
"Valores de fabrica";

const char* lang_select_items =
"English\n"
"Spanish";

const char* get_string(int lang, int index) {
  switch (lang) {
    case LANG_ENGLISH:
      return english[index];
      break;

    case LANG_SPANISH:
      return spanish[index];
      break;

    default:
      return "---";
  }
}

const char* get_menu_items(int lang, int type) {
  switch (lang) {
    case LANG_ENGLISH:
      switch (type) {
        case MENU_LIST_SETTINGS:
          return english_menu_items;
          break;
        case MENU_LIST_LANGUAGES:
          return lang_select_items;
          break;
      }
      break;

    case LANG_SPANISH:
      switch (type) {
        case MENU_LIST_SETTINGS:
          return spanish_menu_items;
          break;
        case MENU_LIST_LANGUAGES:
          return lang_select_items;
          break;
      }
      break;

    default:
      return english_menu_items;
  }

  return "---";
}

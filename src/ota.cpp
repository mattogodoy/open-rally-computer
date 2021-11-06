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


#include <ota.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>
#include <display.h>
#include <memory.h>
#include <release.h>
#include <utils.h>

WiFiClient client;

// Variables to validate response from server
int contentLength = 0;
bool isValidContentType = false;

// The SSID and PWD that the chip needs to connect to
const char* SSID = "OpenRally";
const char* PSWD = "updateorc";

// Server Config
String host = "ota.example.com"; // Host
int port = 80; // Non https. For HTTPS 443. As of today, HTTPS doesn't work.
String build;
String bin;

// Utility to extract header value from headers
String getHeaderValue(String header, String headerName) {
  return header.substring(strlen(headerName.c_str()));
}

void updateScreen() {
  u8g2->firstPage();
  do {
    drawScreen(state.currentScreen);
  } while (u8g2->nextPage());
}

void connectToWiFi() {
  state.updatingFirmware = 1;
  state.currentUpdateStep = UPDATE_CONNECTING;
  updateScreen();

  int timeout = 0;

  Serial.println("Connecting to " + String(SSID));

  // Connect to provided SSID and PSWD
  WiFi.begin(SSID, PSWD);
  WiFi.setHostname("Open Rally Computer");

  // Wait for connection to establish
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("."); // Keep the serial monitor lit!
    delay(500);
    timeout += 500;

    if (timeout >= UPDATE_TIMEOUT) {
      break; // Exit while loop
    }
  }

  // Going back to checkLatestVersion()...
}

void checkLatestVersion() {
  connectToWiFi();

  state.currentUpdateStep = UPDATE_CHECKING;
  updateScreen();

  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    // Connection Succeed
    Serial.println("");
    Serial.println("CONNECTED!");
    Serial.println("Checking for new version...");

    // Check for different board versions
    build = "/orc/" + String(REL_BOARD_VERSION) + "/latest_build.html?sn=" + getSerialNumber() + String("&build=") + String(REL_BUILD); // Add SN to call

    HTTPClient http;
    http.begin("http://" + host + build); //Specify the URL
    int httpCode = http.GET();

    if (httpCode > 0) { //Check for the returning code
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);

      int currentBuild = REL_BUILD;
      int latestBuild = payload.toInt();
      if (latestBuild > currentBuild) {
        Serial.println("There is an update!");
        state.currentUpdateStep = UPDATE_DOWNLOADING;
        updateScreen();

        // Download and install OTA
        execOTA();
      } else {
        Serial.println("You have the latest version");
        state.currentUpdateStep = UPDATE_FINISHED;
        updateScreen();
      }
    } else {
      Serial.println("Error on HTTP request");
      state.currentUpdateStep = UPDATE_UPGR_ERROR;
      updateScreen();
    }

    http.end(); //Free the resources
  } else {
    state.currentUpdateStep = UPDATE_CONN_ERROR;
    updateScreen();
  }
}

// OTA Logic
void execOTA() {
  Serial.println("Connecting to: " + String(host));
  // Connect to host
  if (client.connect(host.c_str(), port)) {
    // Connection Succeed.
    // Check for different board versions
    bin = "/orc/" + String(REL_BOARD_VERSION) + "/firmware.bin";

    Serial.println("Fetching Bin: " + String(bin));

    // Get the contents of the bin file
    client.print(String("GET ") + bin + " HTTP/1.1\r\n" +
      "Host: " + host + "\r\n" +
      "Cache-Control: no-cache\r\n" +
      "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println("Client Timeout !");
        client.stop();
        state.currentUpdateStep = UPDATE_UPGR_ERROR;
        updateScreen();
        return;
      }
    }

    /*
       Response Structure
        HTTP/1.1 200 OK
        x-amz-id-2: NVKxnU1aIQMmpGKhSwpCBh8y2JPbak18QLIfE+OiUDOos+7UftZKjtCFqrwsGOZRN5Zee0jpTd0=
        x-amz-request-id: 2D56B47560B764EC
        Date: Wed, 14 Jun 2017 03:33:59 GMT
        Last-Modified: Fri, 02 Jun 2017 14:50:11 GMT
        ETag: "d2afebbaaebc38cd669ce36727152af9"
        Accept-Ranges: bytes
        Content-Type: application/octet-stream
        Content-Length: 357280
        Server: AmazonS3

        {{BIN FILE CONTENTS}}
    */
    while (client.available()) {
      // Read line untill /n
      String line = client.readStringUntil('\n');
      // Remove space to check if the line is end of headers
      line.trim();

      // Look for the header section end (empty line)
      if (!line.length()) {
        break; // Headers ended. Get the OTA started
      }

      // Check if the HTTP Response is 200. If not, cancel Update
      if (line.startsWith("HTTP/1.1")) {
        if (line.indexOf("200") < 0) {
          Serial.println(line);
          Serial.println("Got a non 200 status code from server. Exiting OTA Update.");
          state.currentUpdateStep = UPDATE_UPGR_ERROR;
          updateScreen();
          break;
        }
      }

      // Extract headers
      // Start with content length
      if (line.startsWith("Content-Length: ")) {
        contentLength = atoi((getHeaderValue(line, "Content-Length: ")).c_str());
        Serial.println("Got " + String(contentLength) + " bytes from server");
      }

      // Next, the content type
      if (line.startsWith("Content-Type: ")) {
        String contentType = getHeaderValue(line, "Content-Type: ");
        Serial.println("Got " + contentType + " payload.");
        if (contentType == "application/octet-stream") {
          isValidContentType = true;
        }
      }
    }
  } else {
    // Connection failed
    Serial.println("Connection to " + String(host) + " failed. Please check your setup");
    state.currentUpdateStep = UPDATE_UPGR_ERROR;
    updateScreen();
  }

  // Check what is the contentLength and if content type is `application/octet-stream`
  Serial.println("contentLength : " + String(contentLength) + ", isValidContentType : " + String(isValidContentType));

  // Check if the necessary data for the OTA is available
  if (contentLength && isValidContentType) {
    bool canBegin = Update.begin(contentLength);

    if (canBegin) {
      state.currentUpdateStep = UPDATE_UPGRADING;
      updateScreen();

      Serial.println("Begin OTA. This may take 2 - 5 mins to complete. Things might be quiet for a while.. Patience!");
      // No activity would appear on the Serial monitor
      // So be patient. This may take 2 - 5mins to complete
      size_t written = Update.writeStream(client);

      if (written == contentLength) {
        Serial.println("Written : " + String(written) + " successfully");
      } else {
        Serial.println("Written only : " + String(written) + "/" + String(contentLength) + ". Retry?");
      }

      if (Update.end()) {
        Serial.println("OTA done!");
        if (Update.isFinished()) {
          // Reset memory to factory defaults
          resetConfig();

          Serial.println("Update successfully completed. Rebooting.");
          ESP.restart();
        } else {
          Serial.println("Update not finished? Something went wrong!");
          state.currentUpdateStep = UPDATE_UPGR_ERROR;
          updateScreen();
        }
      } else {
        Serial.println("Error Occurred. Error #: " + String(Update.getError()));
        state.currentUpdateStep = UPDATE_UPGR_ERROR;
        updateScreen();
      }
    } else {
      // Not enough space to begin OTA
      Serial.println("Not enough space to begin OTA");
      client.flush();
      state.currentUpdateStep = UPDATE_UPGR_ERROR;
      updateScreen();
    }
  } else {
    Serial.println("There was no content in the response");
    client.flush();
    state.currentUpdateStep = UPDATE_UPGR_ERROR;
    updateScreen();
  }
}

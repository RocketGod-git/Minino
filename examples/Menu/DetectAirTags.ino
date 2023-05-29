#include <ArduinoBLE.h>

/*
  Salvador Mendoza - Metabase Q

  LEDs detection - Apple AirTags
  Aug 10th, 2022
*/

#define SCAN_DELAY_MS 500
#define SHOW_DISTANCE_DELAY_MS 2000

// uint8_t advertisement[31];          // Save actual AirTag advertising packet

void detectAirTags() {
  while (true) {
    static unsigned long lastTime = millis();

    // Exit to main menu
    keyboard.loop();
    if (keyboard.left.isPressed()) {
      break;
    }

    // Scan for AirTags every 500ms
    if (millis() - lastTime > SCAN_DELAY_MS) {
      lastTime = millis();
      unsigned long start = millis();
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SH110X_WHITE);
      display.setCursor(0, 0);
      display.println(F("Detect Function"));
      display.println("");

      BLEDevice peripheral = BLE.available();

      if (peripheral) {
        int adLength = peripheral.advertisementData(advertisement, 31);

        if (advertisement[0] == 0x1e && advertisement[2] == 0x4c && advertisement[3] == 0x00) {  // Check if it is an Apple AirTag
          // Show AirTag information until right button is pressed
          while (true) {
            static unsigned long lastTime = millis();
            static bool showDistance = true;

            keyboard.loop();
            if (keyboard.right.isPressed()) {
              break;
            }

            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(SH110X_WHITE);
            display.setCursor(0, 0);
            display.println(F("Airtag detected!"));
            display.println("");

            display.println("Address: ");
            display.println(peripheral.address());
            display.println("");

            // Show distance every 2 seconds
            if (millis() - lastTime > SHOW_DISTANCE_DELAY_MS) {
              lastTime = millis();
              showDistance = !showDistance;
            }

            if (showDistance) {
              rssip(peripheral.rssi());
            } else {
              display.println("Press right to");
              display.println("continue");
            }

            display.display();
          }
        } else {
          display.setTextSize(1);
          display.setTextColor(SH110X_WHITE);
          display.println("Found device, but ");
          display.println("it is not an AirTag");
          display.println("Address: ");
          display.println(peripheral.address());
        }
        display.display();
        Serial.println("Time: " + String(millis() - start) + "ms");
      }
    }
  }
}

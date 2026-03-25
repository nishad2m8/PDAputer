#ifndef SD_MANAGER_H
#define SD_MANAGER_H

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

// M5Cardputer SD card SPI pins (same for standard & ADV)
#define SD_SPI_SCK_PIN  40
#define SD_SPI_MISO_PIN 39
#define SD_SPI_MOSI_PIN 14
#define SD_SPI_CS_PIN   12

namespace SDManager {
    bool begin();
    bool isMounted();
}

#endif // SD_MANAGER_H

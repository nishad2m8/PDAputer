#include "sd_manager.h"

static bool _mounted = false;

bool SDManager::begin() {
    if (_mounted) return true;

    SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);
    _mounted = SD.begin(SD_SPI_CS_PIN, SPI, 25000000);

    if (_mounted)
        Serial.println("[SD] Card mounted");
    else
        Serial.println("[SD] Card mount failed");

    return _mounted;
}

bool SDManager::isMounted() {
    return _mounted;
}

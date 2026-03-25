#ifndef RADIO_MANAGER_H
#define RADIO_MANAGER_H

#include <Arduino.h>
#include "tea5767.h"

#define NUM_PRESETS     6
#define TUNE_STEP       0.1f    // MHz per fine-tune step

#define TEA5767_SDA_PIN 2
#define TEA5767_SCL_PIN 1

#define FM_STATIONS_PATH "/PDAputer/FM Radio/stations.txt"

class RadioManager {
public:
    RadioManager();

    bool begin();
    bool isConnected();

    // --- Tuning ---
    void  tuneUp();
    void  tuneDown();
    void  setFrequency(float freq);
    float getFrequency();

    // --- Seek ---
    void seekUp();
    void seekDown();
    void cancelSeek();
    bool isSeeking();

    // Safely stop all radio activity (cancel seek, save freq, mute)
    void stop();

    // --- Periodic status poll (call from timer) ---
    void updateStatus();

    // --- Live status ---
    bool    isStereo();
    uint8_t getSignalLevel();
    bool    isReady();
    bool    isBandLimit();
    float   getBandMinFreq();
    float   getBandMaxFreq();

    // --- Mute ---
    void toggleMute();
    void setMute(bool m);
    bool isMuted();

    // --- Mute channels ---
    void setMuteLeft(bool m);
    void setMuteRight(bool m);
    bool isMutedLeft();
    bool isMutedRight();

    // --- Presets ---
    void  savePreset(uint8_t idx);
    void  loadPreset(uint8_t idx);
    void  clearPreset(uint8_t idx);
    float getPresetFreq(uint8_t idx);
    bool  hasPreset(uint8_t idx);

    // --- Settings ---
    void    setForceMono(bool mono);
    bool    isForceMono();

    void    setSoftMute(bool en);
    bool    isSoftMute();

    void    setHCC(bool en);
    bool    isHCC();

    void    setSNC(bool en);
    bool    isSNC();

    void    setBand(uint8_t b);      // 0 = US/EU, 1 = JP
    uint8_t getBand();

    void    setDeEmphasis(uint8_t d); // 0 = 50 us, 1 = 75 us
    uint8_t getDeEmphasis();

    void    setSearchLevel(uint8_t l); // 1 = low, 2 = mid, 3 = high
    uint8_t getSearchLevel();

    void setStandby(bool s);
    bool isStandby();

    // --- SD card persistence ---
    void saveSettings();
    void loadSettings();
    void saveLastFrequency();

private:
    TEA5767        _tea;
    TEA5767_Status _status;

    float   _presets[NUM_PRESETS];
    bool    _seeking;
    bool    _seekUp;
    bool    _connected;
    bool    _seekWrapped;
    float   _seekStartFreq;
    unsigned long _seekStartMs;

    unsigned long _lastTuneMs;
    bool          _freqDirty;

    // SD helpers
    String readValue(const char* key, const char* defaultVal = "");
    void   writeValue(const char* key, const char* value);
};

#endif // RADIO_MANAGER_H

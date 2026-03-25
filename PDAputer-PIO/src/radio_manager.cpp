#include "radio_manager.h"
#include <SD.h>

RadioManager::RadioManager()
    : _seeking(false),
      _seekUp(true),
      _connected(false),
      _seekWrapped(false),
      _seekStartFreq(0.0f),
      _seekStartMs(0),
      _lastTuneMs(0),
      _freqDirty(false)
{
    memset(&_status, 0, sizeof(_status));
    for (int i = 0; i < NUM_PRESETS; i++) _presets[i] = 0.0f;
}

// ======================== Init ========================

bool RadioManager::begin() {
    Wire.begin(TEA5767_SDA_PIN, TEA5767_SCL_PIN);
    _connected = _tea.begin(Wire);
    if (_connected) {
        loadSettings();
    }
    return _connected;
}

bool RadioManager::isConnected() { return _connected; }

// ======================== Tuning ========================

void RadioManager::tuneUp() {
    setFrequency(getFrequency() + TUNE_STEP);
}

void RadioManager::tuneDown() {
    setFrequency(getFrequency() - TUNE_STEP);
}

void RadioManager::setFrequency(float freq) {
    float lo = _tea.getBandMin();
    float hi = _tea.getBandMax();
    if (freq < lo) freq = lo;
    if (freq > hi) freq = hi;
    _tea.setFrequency(freq);
    _freqDirty = true;
    _lastTuneMs = millis();
}

float RadioManager::getFrequency() { return _tea.getFrequency(); }

// ======================== Seek ========================

void RadioManager::seekUp() {
    if (_seeking) return;
    _seeking = true;
    _seekUp  = true;
    _seekWrapped = false;
    _seekStartFreq = getFrequency();
    _seekStartMs = millis();
    _tea.setMute(true);
    _tea.seekUp();
}

void RadioManager::seekDown() {
    if (_seeking) return;
    _seeking = true;
    _seekUp  = false;
    _seekWrapped = false;
    _seekStartFreq = getFrequency();
    _seekStartMs = millis();
    _tea.setMute(true);
    _tea.seekDown();
}

void RadioManager::cancelSeek() {
    if (!_seeking) return;
    _seeking = false;
    _tea.setMute(false);
}

bool RadioManager::isSeeking() { return _seeking; }

void RadioManager::stop() {
    cancelSeek();
    if (_connected) {
        saveLastFrequency();
        _tea.setMute(true);
    }
}

// ======================== Status ========================

void RadioManager::updateStatus() {
    if (!_connected) return;
    _status = _tea.readStatus();

    if (_seeking) {
        if (_status.ready || _status.bandLimitReached) {
            _seeking = false;
            _tea.setMute(false);
            _freqDirty = true;
            _lastTuneMs = millis();
        } else if (millis() - _seekStartMs > 10000) {
            cancelSeek();
            setFrequency(_seekStartFreq);
        }
    }

    // Clear dirty flag (no longer saving to SD)
    if (_freqDirty && (millis() - _lastTuneMs > 2000)) {
        _freqDirty = false;
    }
}

bool    RadioManager::isStereo()      { return _status.stereo; }
uint8_t RadioManager::getSignalLevel(){ return _status.signalLevel; }
bool    RadioManager::isReady()       { return _status.ready; }
bool    RadioManager::isBandLimit()   { return _status.bandLimitReached; }
float   RadioManager::getBandMinFreq(){ return _tea.getBandMin(); }
float   RadioManager::getBandMaxFreq(){ return _tea.getBandMax(); }

// ======================== Mute ========================

void RadioManager::toggleMute()      { _tea.setMute(!_tea.isMuted()); }
void RadioManager::setMute(bool m)   { _tea.setMute(m); }
bool RadioManager::isMuted()         { return _tea.isMuted(); }
void RadioManager::setMuteLeft(bool m)  { _tea.setMuteLeft(m); }
void RadioManager::setMuteRight(bool m) { _tea.setMuteRight(m); }
bool RadioManager::isMutedLeft()        { return _tea.isMutedLeft(); }
bool RadioManager::isMutedRight()       { return _tea.isMutedRight(); }

// ======================== Presets ========================

void RadioManager::savePreset(uint8_t idx) {
    if (idx >= NUM_PRESETS) return;
    _presets[idx] = getFrequency();

    char key[12], val[12];
    snprintf(key, sizeof(key), "%d", idx + 1);
    snprintf(val, sizeof(val), "%.1f", _presets[idx]);
    writeValue(key, val);
}

void RadioManager::clearPreset(uint8_t idx) {
    if (idx >= NUM_PRESETS) return;
    _presets[idx] = 0.0f;

    char key[12];
    snprintf(key, sizeof(key), "%d", idx + 1);
    writeValue(key, "0.0");
}

void RadioManager::loadPreset(uint8_t idx) {
    if (idx >= NUM_PRESETS || _presets[idx] <= 0.0f) return;
    setFrequency(_presets[idx]);
}

float RadioManager::getPresetFreq(uint8_t idx) {
    return (idx < NUM_PRESETS) ? _presets[idx] : 0.0f;
}

bool RadioManager::hasPreset(uint8_t idx) {
    return (idx < NUM_PRESETS) && (_presets[idx] > 0.0f);
}

// ======================== Settings ========================

void RadioManager::setForceMono(bool mono) { if (_connected) _tea.setForceMono(mono); saveSettings(); }
bool RadioManager::isForceMono()           { return _tea.isForceMono(); }

void RadioManager::setSoftMute(bool en)    { if (_connected) _tea.setSoftMute(en); saveSettings(); }
bool RadioManager::isSoftMute()            { return _tea.isSoftMute(); }

void RadioManager::setHCC(bool en)         { if (_connected) _tea.setHighCutControl(en); saveSettings(); }
bool RadioManager::isHCC()                 { return _tea.isHighCutControl(); }

void RadioManager::setSNC(bool en)         { if (_connected) _tea.setStereoNoiseCancelling(en); saveSettings(); }
bool RadioManager::isSNC()                 { return _tea.isStereoNoiseCancelling(); }

void RadioManager::setBand(uint8_t b) {
    if (!_connected) return;
    _tea.setBand((TEA5767_Band)b);
    float freq = getFrequency();
    float lo   = _tea.getBandMin();
    float hi   = _tea.getBandMax();
    if (freq < lo) freq = lo;
    if (freq > hi) freq = hi;
    setFrequency(freq);
    saveSettings();
}
uint8_t RadioManager::getBand() { return (uint8_t)_tea.getBand(); }

void    RadioManager::setDeEmphasis(uint8_t d) { if (_connected) _tea.setDeEmphasis((TEA5767_DeEmphasis)d); saveSettings(); }
uint8_t RadioManager::getDeEmphasis()          { return (uint8_t)_tea.getDeEmphasis(); }

void    RadioManager::setSearchLevel(uint8_t l) { _tea.setSearchLevel((TEA5767_SearchLevel)l); saveSettings(); }
uint8_t RadioManager::getSearchLevel()          { return (uint8_t)_tea.getSearchLevel(); }

void RadioManager::setStandby(bool s) { if (_connected) _tea.setStandby(s); saveSettings(); }
bool RadioManager::isStandby()        { return _tea.isStandby(); }

// ======================== SD Card Persistence ========================

String RadioManager::readValue(const char* key, const char* defaultVal) {
    File f = SD.open(FM_STATIONS_PATH, FILE_READ);
    if (!f) return String(defaultVal);

    while (f.available()) {
        String line = f.readStringUntil('\n');
        line.trim();
        if (line.length() == 0 || line[0] == '#') continue;

        int eq = line.indexOf('=');
        if (eq < 0) continue;

        String k = line.substring(0, eq);
        k.trim();
        if (k == key) {
            String v = line.substring(eq + 1);
            v.trim();
            f.close();
            return v;
        }
    }
    f.close();
    return String(defaultVal);
}

void RadioManager::writeValue(const char* key, const char* value) {
    // Read all lines, update matching key or append
    String content;
    bool found = false;

    File f = SD.open(FM_STATIONS_PATH, FILE_READ);
    if (f) {
        while (f.available()) {
            String line = f.readStringUntil('\n');
            String trimmed = line;
            trimmed.trim();

            if (trimmed.length() > 0 && trimmed[0] != '#') {
                int eq = trimmed.indexOf('=');
                if (eq >= 0) {
                    String k = trimmed.substring(0, eq);
                    k.trim();
                    if (k == key) {
                        content += String(key) + " = " + String(value) + "\n";
                        found = true;
                        continue;
                    }
                }
            }
            content += line + "\n";
        }
        f.close();
    }

    if (!found) {
        content += String(key) + " = " + String(value) + "\n";
    }

    // Ensure directory exists
    SD.mkdir("/PDAputer/FM Radio");

    f = SD.open(FM_STATIONS_PATH, FILE_WRITE);
    if (f) {
        f.print(content);
        f.close();
    }
}

void RadioManager::saveSettings() {
    // Settings are hardcoded defaults, no persistence needed
}

void RadioManager::loadSettings() {
    // Hardcoded defaults
    _tea.setForceMono(false);
    _tea.setSoftMute(true);
    _tea.setHighCutControl(true);
    _tea.setStereoNoiseCancelling(true);
    _tea.setBand((TEA5767_Band)0);
    _tea.setDeEmphasis((TEA5767_DeEmphasis)1);
    _tea.setSearchLevel((TEA5767_SearchLevel)2);
    _tea.setStandby(false);

    // Load presets from SD
    for (int i = 0; i < NUM_PRESETS; i++) {
        char key[4];
        snprintf(key, sizeof(key), "%d", i + 1);
        _presets[i] = readValue(key, "0.0").toFloat();
    }

    // Tune to first available preset, or default 98.5
    float startFreq = 98.5f;
    for (int i = 0; i < NUM_PRESETS; i++) {
        if (_presets[i] > 0.0f) {
            startFreq = _presets[i];
            break;
        }
    }
    _tea.setFrequency(startFreq);
}

void RadioManager::saveLastFrequency() {
    // No-op: avoid frequent SD writes that damage the card
}

#ifndef TEA5767_H
#define TEA5767_H

#include <Arduino.h>
#include <Wire.h>

#define TEA5767_ADDR 0x60

// Band frequency limits (MHz)
#define TEA5767_US_EU_MIN 87.5f
#define TEA5767_US_EU_MAX 108.0f
#define TEA5767_JP_MIN    76.0f
#define TEA5767_JP_MAX    91.0f

enum TEA5767_SearchLevel : uint8_t {
    TEA5767_SEARCH_LOW  = 1,
    TEA5767_SEARCH_MID  = 2,
    TEA5767_SEARCH_HIGH = 3
};

enum TEA5767_Band : uint8_t {
    TEA5767_BAND_US_EU = 0,
    TEA5767_BAND_JP    = 1
};

enum TEA5767_DeEmphasis : uint8_t {
    TEA5767_DEEMPH_50 = 0,   // 50us (Europe, Australia, Japan)
    TEA5767_DEEMPH_75 = 1    // 75us (USA)
};

struct TEA5767_Status {
    bool     ready;
    bool     bandLimitReached;
    float    frequency;
    bool     stereo;
    uint8_t  signalLevel;   // 0-15
    uint8_t  ifCounter;     // IF counter result
    uint8_t  chipId;
};

class TEA5767 {
public:
    TEA5767();

    bool begin(TwoWire &wire);
    bool isConnected();

    // --- Tuning ---
    void  setFrequency(float freqMHz);
    float getFrequency();

    // --- Seek / Search ---
    void seekUp();
    void seekDown();
    void setSearchLevel(TEA5767_SearchLevel level);
    TEA5767_SearchLevel getSearchLevel();

    // --- Mute ---
    void setMute(bool mute);
    bool isMuted();
    void setMuteLeft(bool mute);
    void setMuteRight(bool mute);
    bool isMutedLeft();
    bool isMutedRight();

    // --- Stereo / Mono ---
    void setForceMono(bool mono);
    bool isForceMono();

    // --- Band ---
    void setBand(TEA5767_Band band);
    TEA5767_Band getBand();
    float getBandMin();
    float getBandMax();

    // --- Advanced Features ---
    void setSoftMute(bool enable);
    bool isSoftMute();

    void setHighCutControl(bool enable);
    bool isHighCutControl();

    void setStereoNoiseCancelling(bool enable);
    bool isStereoNoiseCancelling();

    void setDeEmphasis(TEA5767_DeEmphasis de);
    TEA5767_DeEmphasis getDeEmphasis();

    void setStandby(bool standby);
    bool isStandby();

    void setHighSideInjection(bool high);
    bool isHighSideInjection();

    void setSWPort1(bool state);
    void setSWPort2(bool state);

    // --- Status Readback ---
    TEA5767_Status readStatus();

private:
    TwoWire *_wire;
    uint8_t  _writeReg[5];
    uint8_t  _readReg[5];

    float               _frequency;
    bool                _mute;
    bool                _muteLeft;
    bool                _muteRight;
    bool                _forceMono;
    bool                _standby;
    bool                _softMute;
    bool                _hcc;
    bool                _snc;
    bool                _hlsi;
    bool                _swp1;
    bool                _swp2;
    TEA5767_Band        _band;
    TEA5767_DeEmphasis  _deEmphasis;
    TEA5767_SearchLevel _searchLevel;

    void     _transmit();
    void     _receive();
    void     _buildWriteRegisters();
    uint16_t _freqToPLL(float freqMHz);
    float    _pllToFreq(uint16_t pll);
};

#endif // TEA5767_H

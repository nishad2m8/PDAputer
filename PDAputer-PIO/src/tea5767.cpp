#include "tea5767.h"

TEA5767::TEA5767()
    : _wire(nullptr),
      _frequency(98.5f),
      _mute(false),
      _muteLeft(false),
      _muteRight(false),
      _forceMono(false),
      _standby(false),
      _softMute(true),
      _hcc(true),
      _snc(true),
      _hlsi(true),
      _swp1(false),
      _swp2(false),
      _band(TEA5767_BAND_US_EU),
      _deEmphasis(TEA5767_DEEMPH_75),
      _searchLevel(TEA5767_SEARCH_MID)
{
    memset(_writeReg, 0, 5);
    memset(_readReg, 0, 5);
}

bool TEA5767::begin(TwoWire &wire) {
    _wire = &wire;
    if (!isConnected()) return false;
    setFrequency(_frequency);
    return true;
}

bool TEA5767::isConnected() {
    if (!_wire) return false;
    _wire->beginTransmission(TEA5767_ADDR);
    return (_wire->endTransmission() == 0);
}

// ======================== Tuning ========================

void TEA5767::setFrequency(float freqMHz) {
    float lo = getBandMin();
    float hi = getBandMax();
    if (freqMHz < lo) freqMHz = lo;
    if (freqMHz > hi) freqMHz = hi;

    _frequency = freqMHz;
    _buildWriteRegisters();
    _writeReg[0] &= ~0x40;   // Clear search-mode bit
    _transmit();
}

float TEA5767::getFrequency() { return _frequency; }

// ======================== Seek ========================

void TEA5767::seekUp() {
    _buildWriteRegisters();
    _writeReg[0] |=  0x40;   // SM = 1
    _writeReg[2] |=  0x80;   // SUD = 1 (up)
    _transmit();
}

void TEA5767::seekDown() {
    _buildWriteRegisters();
    _writeReg[0] |=  0x40;   // SM = 1
    _writeReg[2] &= ~0x80;   // SUD = 0 (down)
    _transmit();
}

void TEA5767::setSearchLevel(TEA5767_SearchLevel level) { _searchLevel = level; }
TEA5767_SearchLevel TEA5767::getSearchLevel() { return _searchLevel; }

// ======================== Mute ========================

void TEA5767::setMute(bool mute)      { _mute = mute; setFrequency(_frequency); }
bool TEA5767::isMuted()               { return _mute; }
void TEA5767::setMuteLeft(bool mute)  { _muteLeft = mute;  setFrequency(_frequency); }
void TEA5767::setMuteRight(bool mute) { _muteRight = mute; setFrequency(_frequency); }
bool TEA5767::isMutedLeft()           { return _muteLeft; }
bool TEA5767::isMutedRight()          { return _muteRight; }

// ======================== Stereo / Mono ========================

void TEA5767::setForceMono(bool mono) { _forceMono = mono; setFrequency(_frequency); }
bool TEA5767::isForceMono()           { return _forceMono; }

// ======================== Band ========================

void TEA5767::setBand(TEA5767_Band band) { _band = band; }
TEA5767_Band TEA5767::getBand()          { return _band; }

float TEA5767::getBandMin() {
    return (_band == TEA5767_BAND_JP) ? TEA5767_JP_MIN : TEA5767_US_EU_MIN;
}

float TEA5767::getBandMax() {
    return (_band == TEA5767_BAND_JP) ? TEA5767_JP_MAX : TEA5767_US_EU_MAX;
}

// ======================== Advanced Features ========================

void TEA5767::setSoftMute(bool enable)           { _softMute = enable; setFrequency(_frequency); }
bool TEA5767::isSoftMute()                       { return _softMute; }

void TEA5767::setHighCutControl(bool enable)     { _hcc = enable; setFrequency(_frequency); }
bool TEA5767::isHighCutControl()                 { return _hcc; }

void TEA5767::setStereoNoiseCancelling(bool en)  { _snc = en; setFrequency(_frequency); }
bool TEA5767::isStereoNoiseCancelling()          { return _snc; }

void TEA5767::setDeEmphasis(TEA5767_DeEmphasis de) { _deEmphasis = de; setFrequency(_frequency); }
TEA5767_DeEmphasis TEA5767::getDeEmphasis()        { return _deEmphasis; }

void TEA5767::setStandby(bool standby) { _standby = standby; setFrequency(_frequency); }
bool TEA5767::isStandby()              { return _standby; }

void TEA5767::setHighSideInjection(bool high) { _hlsi = high; }
bool TEA5767::isHighSideInjection()           { return _hlsi; }

void TEA5767::setSWPort1(bool state) { _swp1 = state; setFrequency(_frequency); }
void TEA5767::setSWPort2(bool state) { _swp2 = state; setFrequency(_frequency); }

// ======================== Status Readback ========================

TEA5767_Status TEA5767::readStatus() {
    _receive();

    TEA5767_Status s;
    s.ready            = (_readReg[0] & 0x80) != 0;
    s.bandLimitReached = (_readReg[0] & 0x40) != 0;

    uint16_t pll = (((uint16_t)_readReg[0] & 0x3F) << 8) | _readReg[1];
    s.frequency = _pllToFreq(pll);

    s.stereo      = (_readReg[2] & 0x80) != 0;
    s.ifCounter   = _readReg[2] & 0x7F;
    s.signalLevel = (_readReg[3] >> 4) & 0x0F;
    s.chipId      = (_readReg[3] >> 1) & 0x07;

    return s;
}

// ======================== Private ========================

void TEA5767::_transmit() {
    if (!_wire) return;
    _wire->beginTransmission(TEA5767_ADDR);
    _wire->write(_writeReg, 5);
    _wire->endTransmission();
}

void TEA5767::_receive() {
    if (!_wire) return;
    memset(_readReg, 0, 5);
    _wire->requestFrom((uint8_t)TEA5767_ADDR, (uint8_t)5);
    for (int i = 0; i < 5 && _wire->available(); i++) {
        _readReg[i] = _wire->read();
    }
}

void TEA5767::_buildWriteRegisters() {
    uint16_t pll = _freqToPLL(_frequency);

    // Byte 0: MUTE | SM | PLL[13:8]
    _writeReg[0] = (pll >> 8) & 0x3F;
    if (_mute) _writeReg[0] |= 0x80;

    // Byte 1: PLL[7:0]
    _writeReg[1] = pll & 0xFF;

    // Byte 2: SUD | SSL[1:0] | HLSI | MS | MR | ML | SWP1
    _writeReg[2] = 0;
    _writeReg[2] |= ((_searchLevel & 0x03) << 5);   // SSL
    if (_hlsi)      _writeReg[2] |= 0x10;            // HLSI
    if (_forceMono) _writeReg[2] |= 0x08;            // MS
    if (_muteRight) _writeReg[2] |= 0x04;            // MR
    if (_muteLeft)  _writeReg[2] |= 0x02;            // ML
    if (_swp1)      _writeReg[2] |= 0x01;            // SWP1

    // Byte 3: SWP2 | STBY | BL | XTAL | SMUTE | HCC | SNC | SI
    _writeReg[3] = 0;
    if (_swp2)     _writeReg[3] |= 0x80;
    if (_standby)  _writeReg[3] |= 0x40;
    if (_band == TEA5767_BAND_JP) _writeReg[3] |= 0x20;
    _writeReg[3] |= 0x10;                             // XTAL = 1 (32.768 kHz crystal)
    if (_softMute) _writeReg[3] |= 0x08;
    if (_hcc)      _writeReg[3] |= 0x04;
    if (_snc)      _writeReg[3] |= 0x02;
    // SI = 0

    // Byte 4: PLLREF | DTC | 0 0 0 0 0 0
    _writeReg[4] = 0;
    // PLLREF = 0 (use 32.768 kHz crystal, not 6.5 MHz)
    if (_deEmphasis == TEA5767_DEEMPH_75) _writeReg[4] |= 0x40;  // DTC
}

uint16_t TEA5767::_freqToPLL(float freqMHz) {
    // High-side injection: PLL = 4 * (f_RF + f_IF) / f_ref
    // f_IF = 225 kHz, f_ref = 32.768 kHz
    return (uint16_t)(4.0f * (freqMHz * 1000000.0f + 225000.0f) / 32768.0f);
}

float TEA5767::_pllToFreq(uint16_t pll) {
    if (pll == 0) return 0.0f;
    return ((float)pll * 32768.0f / 4.0f - 225000.0f) / 1000000.0f;
}

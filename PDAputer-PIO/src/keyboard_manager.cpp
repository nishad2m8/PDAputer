#include "keyboard_manager.h"
#include <M5Cardputer.h>
#include <array>

// HID key codes returned by M5Cardputer getKey() for special keys
#define HID_BACKSPACE 0x2a
#define HID_TAB       0x2b
#define HID_ENTER     0x28

namespace KeyboardManager {

static std::function<void(char)> s_on_key;
static std::array<bool, 256> s_prev{};
static bool s_prev_del   = false;
static bool s_prev_enter = false;
static bool s_prev_tab   = false;

void begin(std::function<void(char)> onKeyPress) {
    s_on_key = onKeyPress;
    s_prev.fill(false);
    s_prev_del = false;
    s_prev_enter = false;
    s_prev_tab = false;
}

void update() {
    if (!s_on_key) return;

    auto& status = M5Cardputer.Keyboard.keysState();

    // --- Special keys via flags (edge-triggered) ---
    // These flags let us distinguish special keys from their char collisions:
    //   ENTER (flag) vs '(' (Shift+9)
    //   BACKSPACE (flag) vs '*' (Shift+8)
    //   TAB (flag) vs '+' (Shift+=)

    if (status.del && !s_prev_del) {
        Serial.printf("[KB] dispatch BACKSPACE (0x08)\n");
        s_on_key(KEY_CODE_BACKSPACE);
    }
    if (status.enter && !s_prev_enter) {
        Serial.printf("[KB] dispatch ENTER (0x0A)\n");
        s_on_key(KEY_CODE_ENTER);
    }
    if (status.tab && !s_prev_tab) {
        Serial.printf("[KB] dispatch TAB (0x09)\n");
        s_on_key(KEY_CODE_TAB);
    }

    s_prev_del   = status.del;
    s_prev_enter = status.enter;
    s_prev_tab   = status.tab;

    // --- Regular characters from word vector ---
    // Build current keymap, skipping chars that collide with active special keys
    std::array<bool, 256> current{};

    for (auto c : status.word) {
        if (c == 0) continue;
        // Skip HID codes when corresponding special key flag is active
        if (c == (char)HID_ENTER     && status.enter) continue;
        if (c == (char)HID_BACKSPACE  && status.del)   continue;
        if (c == (char)HID_TAB       && status.tab)    continue;
        current[static_cast<uint8_t>(c)] = true;
    }

    // Dispatch on key-down transitions
    for (size_t idx = 0; idx < current.size(); ++idx) {
        if (current[idx] && !s_prev[idx]) {
            char key = (char)idx;
            Serial.printf("[KB] dispatch '%c' (0x%02X)\n",
                          (key >= 32 && key < 127) ? key : '.', (uint8_t)key);
            s_on_key(key);
        }
    }

    s_prev = current;
}

} // namespace KeyboardManager

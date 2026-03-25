#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include <Arduino.h>
#include <functional>

// Standard key codes dispatched to apps
#define KEY_CODE_BACKSPACE  0x08
#define KEY_CODE_TAB        0x09
#define KEY_CODE_ENTER      '\n'
#define KEY_CODE_SPACE      ' '

namespace KeyboardManager {
    // Initialize the keyboard manager
    void begin(std::function<void(char)> onKeyPress);

    // Call every loop iteration after M5Cardputer.update()
    void update();
}

#endif // KEYBOARD_MANAGER_H

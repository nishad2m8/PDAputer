#pragma once

#include "../../app_manager/app_base.h"
#include "../../app_manager/app_manager.h"
#include <smooth_ui_toolkit.h>

using namespace smooth_ui_toolkit;

class BootApp : public AppBase {
public:
    BootApp(AppManager& manager) : _manager(manager) {}

    void onCreate() override;
    void onUpdate() override;
    void onDestroy() override;
    const char* getName() override { return "Boot"; }

    void setNextApp(AppBase* next) { _next_app = next; }

private:
    AppManager& _manager;
    AppBase* _next_app = nullptr;

    enum Phase {
        PHASE_TYPING_NAME,
        PHASE_FORMING_CONTRIBUTION,
        PHASE_WAITING,
        PHASE_DONE
    };

    Phase _phase = PHASE_TYPING_NAME;

    Animate _name_anim;
    static constexpr const char* NAME_TEXT = "PDAputer";
    static constexpr int NAME_LEN = 8;
    int _last_name_chars = 0;

    // Tone settings for typing sound
    static constexpr int TONE_BASE = 3000;
    static constexpr int TONE_STEP = 200;
    static constexpr int TONE_MS   = 20;

    Animate _contrib_anim;
    static constexpr const char* CONTRIB_TEXT = "nishad2m8";
    static constexpr int CONTRIB_LEN = 9;
    char _contrib_buf[16];
    uint32_t _last_random_update = 0;

    uint32_t _wait_start = 0;
    static constexpr uint32_t WAIT_DURATION_MS = 3000;

    char randomChar();
    void updateTypingName();
    void updateFormingContribution();
    void updateWaiting();
};

#pragma once

class AppBase {
public:
    virtual ~AppBase() = default;
    virtual void onCreate() = 0;
    virtual void onUpdate() = 0;
    virtual void onDestroy() = 0;
    virtual void onKeyPressed(char key) {}
    virtual const char* getName() = 0;
};

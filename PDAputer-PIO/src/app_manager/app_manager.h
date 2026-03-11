#pragma once

#include "app_base.h"
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

class AppManager {
public:
    void init();
    void update();
    void startApp(AppBase* app);
    void switchApp(AppBase* app);
    void handleKey(char key);
    AppBase* currentApp();

    static SemaphoreHandle_t lvglMutex;

private:
    AppBase* _current_app = nullptr;
    AppBase* _next_app = nullptr;
};

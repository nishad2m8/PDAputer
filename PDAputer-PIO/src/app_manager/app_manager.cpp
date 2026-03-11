#include "app_manager.h"

SemaphoreHandle_t AppManager::lvglMutex = nullptr;

void AppManager::init() {
    lvglMutex = xSemaphoreCreateMutex();
}

void AppManager::update() {
    if (_next_app != nullptr) {
        if (_current_app) {
            _current_app->onDestroy();
        }
        _current_app = _next_app;
        _next_app = nullptr;
        _current_app->onCreate();
    }

    if (_current_app) {
        _current_app->onUpdate();
    }
}

void AppManager::startApp(AppBase* app) {
    _next_app = app;
}

void AppManager::switchApp(AppBase* app) {
    _next_app = app;
}

void AppManager::handleKey(char key) {
    if (_current_app) {
        _current_app->onKeyPressed(key);
    }
}

AppBase* AppManager::currentApp() {
    return _current_app;
}

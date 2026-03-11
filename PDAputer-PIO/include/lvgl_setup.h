#ifndef LVGL_SETUP_H
#define LVGL_SETUP_H

#include <lvgl.h>
#include <M5Cardputer.h>

// Number of lines to allocate for the buffer
#define BUFFER_LINES 20

/**
 * @brief Initialize LVGL and configure the display for M5Cardputer.
 */
inline void lvgl_setup() {
    // Initialize LVGL
    lv_init();

    // Create LVGL display with 240x135 resolution
    static lv_display_t *disp = lv_display_create(240, 135);
    if (disp == NULL) {
        LV_LOG_ERROR("lv_display_create failed");
        return;
    }

    // Link M5.Display to LVGL
    lv_display_set_driver_data(disp, &M5.Display);

    // Set flush callback using M5.Display
    lv_display_set_flush_cb(disp, [](lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
        auto *gfx = (M5GFX *)lv_display_get_driver_data(disp);
        uint32_t w = (area->x2 - area->x1 + 1);
        uint32_t h = (area->y2 - area->y1 + 1);

        gfx->startWrite();
        gfx->setAddrWindow(area->x1, area->y1, w, h);
        gfx->writePixels((lgfx::rgb565_t *)px_map, w * h);
        gfx->endWrite();

        lv_display_flush_ready(disp);
    });

    // Buffer setup for devices without PSRAM
    // RGB565 -> 2 bytes per pixel
    const size_t buf_bytes = (size_t)240 * BUFFER_LINES * sizeof(lv_color_t);
    static lv_color_t *buf1 = (lv_color_t *)malloc(buf_bytes);
    if (buf1 == NULL) {
        LV_LOG_ERROR("Memory allocation failed for buf1");
        return;
    }
    lv_display_set_buffers(disp, (void *)buf1, NULL, buf_bytes, LV_DISPLAY_RENDER_MODE_PARTIAL);
}

/**
 * @brief Tick handler function for LVGL (to be run as a FreeRTOS task).
 * @param arg Optional argument (not used).
 */
inline void lv_tick_task(void *arg) {
    while (1) {
        lv_tick_inc(10);          // Increment LVGL tick by 10ms
        vTaskDelay(pdMS_TO_TICKS(10));  // Delay 10ms
    }
}

#endif // LVGL_SETUP_H

#include "esp_check.h"
#include "esp_err.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_lvgl_port.h"
#include "bsp_display.h"
#include "bsp_touch.h"
#include "touch_display.h"
#include "screensaver.h"

static void global_touch_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_PRESSED)
    {
        screensaver_reset();
    }
}

void touch_display_init()
{
    /* Initialize display */
    AXS15231B_display_init();

    /* Initialize LVGL port */
    lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    lvgl_cfg.task_priority = CONFIG_ESP32S3_LVGL_TASK_PRIORITY;
    lvgl_cfg.timer_period_ms = CONFIG_ESP32S3_LVGL_TIMER_PERIOD_MS;
    ESP_ERROR_CHECK(lvgl_port_init(&lvgl_cfg));

    /* Add display */
    lv_display_t *lvgl_disp = LVGL_display_add();
    lv_display_set_rotation(lvgl_disp, LV_DISP_ROTATION_0);

    /* Turn on backlight */
    ESP_ERROR_CHECK(bsp_display_brightness_set(CONFIG_ESP32S3_SCREEN_BRIGHTNESS));

    /* Initialize screensaver */
    screensaver_init(CONFIG_ESP32S3_SCREENSAVER_TIMEOUT); // Set screensaver to activate after configured seconds of inactivity

    /* Add touch hardware */
    AXS15231B_touch_init();
    lv_indev_t *lvgl_touch = LVGL_touch_add(lvgl_disp);

    /* Add global touch event callback to reset screensaver on touch */
    lv_indev_add_event_cb(lvgl_touch, global_touch_cb, LV_EVENT_PRESSED, NULL);
}
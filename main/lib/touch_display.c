#include "esp_check.h"
#include "esp_err.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_lvgl_port.h"
#include "bsp_display.h"
#include "bsp_touch.h"
#include "touch_display.h"
#include "screensaver.h"

static const char *TAG = "touch_display";

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
    ESP_LOGI(TAG, "Starting LCD Touch Example");

    /* Initialize display and touch hardware */
    AXS15231B_display_init();
    AXS15231B_touch_init();

    /* Initialize LVGL port */
    lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    lvgl_cfg.task_priority = CONFIG_ESP32S3_LVGL_TASK_PRIORITY;
    lvgl_cfg.timer_period_ms = CONFIG_ESP32S3_LVGL_TIMER_PERIOD_MS;
    ESP_ERROR_CHECK(lvgl_port_init(&lvgl_cfg));

    /* Add display and touch to LVGL */
    lv_display_t *lvgl_disp = LVGL_display_add();
    if (lvgl_disp == NULL)
    {
        ESP_LOGE(TAG, "Failed to create LVGL display");
        return;
    }

    lv_indev_t *lvgl_touch = LVGL_touch_add(lvgl_disp);
    if (lvgl_touch == NULL)
    {
        ESP_LOGW(TAG, "Touch input not available");
    }

    lv_display_set_rotation(lvgl_disp, LV_DISP_ROTATION_0);

    /* Turn on backlight */
    ESP_ERROR_CHECK(bsp_display_brightness_set(CONFIG_ESP32S3_SCREEN_BRIGHTNESS));

    /* Initialize screensaver */

    // Attach callback directly to the first input device, the tocuchscreen:
    lv_indev_t *indev = lv_indev_get_next(NULL);
    lv_indev_add_event_cb(indev, global_touch_cb, LV_EVENT_PRESSED, NULL);

    screensaver_init(CONFIG_ESP32S3_SCREENSAVER_TIMEOUT); // Set screensaver to activate after configured seconds of inactivity
}
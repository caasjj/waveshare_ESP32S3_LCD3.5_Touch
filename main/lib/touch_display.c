#include "esp_check.h"
#include "esp_err.h"
#include "esp_log.h"

#include "esp_lvgl_port.h"
#include "bsp_display.h"
#include "bsp_touch.h"
#include "touch_display.h"
#include "screensaver.h"

static const char *TAG = "touch_display";

void touch_display_init()
{
    ESP_LOGI(TAG, "Starting LCD Touch Example");

    /* Initialize display and touch hardware */
    AXS15231B_display_init();
    AXS15231B_touch_init();

    /* Initialize LVGL port */
    lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    lvgl_cfg.task_priority = 2;
    lvgl_cfg.timer_period_ms = 40;
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
    ESP_ERROR_CHECK(bsp_display_brightness_set(75));
}
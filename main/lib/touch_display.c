#include "esp_check.h"
#include "esp_err.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_lvgl_port.h"
#include "bsp_display.h"
#include "bsp_touch.h"
#include "touch_display.h"
#include "screensaver.h"

esp_err_t screensleep(void)
{
    lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
    return bsp_display_sleep();
}

esp_err_t screenwake(void)
{
    lv_obj_remove_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
    return bsp_display_wake();
}

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
    lv_display_t *lvgl_disp = AXS15231B_display_init();

    /* Add touch hardware */
    lv_indev_t *lvgl_touch = AXS15231B_touch_init(lvgl_disp);

    /* Initialize screensaver */
    screensaver_init(CONFIG_ESP32S3_SCREENSAVER_TIMEOUT, &screensleep, &screenwake); // Set screensaver to activate after configured seconds of inactivity
    lv_indev_add_event_cb(lvgl_touch, global_touch_cb, LV_EVENT_PRESSED, NULL);
}
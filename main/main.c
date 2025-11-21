#include "driver/gpio.h"
#include "driver/i2c.h"
#include "driver/ledc.h"
#include "driver/spi_master.h"
#include "esp_check.h"
#include "esp_err.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_io_interface.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_log.h"
#include "esp_random.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lv_demos.h"
#include "lvgl.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/lock.h>
#include <sys/param.h>
#include <unistd.h>
#include "bsp_display.h"
#include "bsp_touch.h"

/* Тег для логирования */
static const char *TAG = "lcd_touch_example";

static void btn_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *btn = lv_event_get_target_obj(e);
    if (code == LV_EVENT_CLICKED)
    {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t *label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Button: %d", cnt);

        /* Get display from the button's screen */
        lv_display_t *disp = lv_obj_get_display(btn);
        if (cnt % 2 == 0)
            lv_display_set_rotation(disp, LV_DISP_ROTATION_0);
        else
            lv_display_set_rotation(disp, LV_DISP_ROTATION_270);
    }
}

/**
 * Create a button with a label and react on click event.
 */
void lv_example_get_started_2(void)
{
    lv_obj_t *btn = lv_button_create(lv_screen_active());       /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                                /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                              /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL); /*Assign a callback to the button*/

    lv_obj_t *label = lv_label_create(btn); /*Add a label to the button*/
    lv_label_set_text(label, "Button");     /*Set the labels text*/
    lv_obj_center(label);
}

void app_main(void)
{
    ESP_LOGI(TAG, "Starting LCD Touch Example");

    /* Initialize hardware peripherals */
    ESP_ERROR_CHECK(bsp_display_brightness_init());
    ESP_ERROR_CHECK(bsp_display_brightness_set(0));
    touch_i2c_init();

    /* Initialize display and touch hardware */
    Initialize_AXS15231B_Display();
    Initialize_AXS15231B_Touch();

    /* Initialize LVGL port */
    lvgl_port_cfg_t lvgl_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    lvgl_cfg.task_priority = 2;
    lvgl_cfg.timer_period_ms = 40;
    ESP_ERROR_CHECK(lvgl_port_init(&lvgl_cfg));

    /* Add display and touch to LVGL */
    lv_display_t *lvgl_disp = Add_LVGL_Display();
    if (lvgl_disp == NULL)
    {
        ESP_LOGE(TAG, "Failed to create LVGL display");
        return;
    }

    lv_indev_t *lvgl_touch = Add_LVGL_Touch(lvgl_disp);
    if (lvgl_touch == NULL)
    {
        ESP_LOGW(TAG, "Touch input not available");
    }

    lv_display_set_rotation(lvgl_disp, LV_DISP_ROTATION_0);

    /* Turn on backlight */
    ESP_ERROR_CHECK(bsp_display_brightness_set(50));

    lvgl_port_lock(0);

    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);

    /*Create a white label, set its text and align it to the center*/
    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello world");
    lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    lv_example_get_started_2();

    lvgl_port_unlock();
}

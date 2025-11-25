#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_err.h"
#include "esp_log.h"

#include "lvgl.h"
#include "esp_lvgl_port.h"
#include "lib/touch_display.h"
#include "lib/freertos_timer_utils.h"
#include "template.h"

static const char *TAG = "main";

void app_main(void)
{
    touch_display_init();
    ESP_LOGI(TAG, "LVGL example started");

    lvgl_port_lock(0);

    template_screen_create();

    lvgl_port_unlock();

    while (1)
    {

#if CONFIG_ESP32S3_PROGRAM_ENABLE_TIMER_WATERMARK_MONITORING
        monitor_timer_task_stack_watermark();
#endif
        vTaskDelay(pdMS_TO_TICKS(5000));
        ESP_LOGI(TAG, "Main task heartbeat ...");
    }
}

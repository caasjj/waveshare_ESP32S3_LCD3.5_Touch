#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_err.h"
#include "esp_log.h"

#include "lvgl.h"
#include "esp_lvgl_port.h"
#include "lib/touch_display.h"
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
#ifdef CONFIG_TIMER_TASK_STACK_MONITORING
        TaskHandle_t timer_task = xTimerGetTimerDaemonTaskHandle();
        if (timer_task != NULL)
        {
            UBaseType_t high_water_mark = uxTaskGetStackHighWaterMark(timer_task);
            printf("Timer task minimum free stack: %u words\n", (unsigned)high_water_mark);
        }
#endif
        vTaskDelay(pdMS_TO_TICKS(5000));
        ESP_LOGI(TAG, "Main task heartbeat ...");
    }
}

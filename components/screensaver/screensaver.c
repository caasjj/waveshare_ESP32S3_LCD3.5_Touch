#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "bsp_display.h"
#include "screensaver.h"
#include "esp_log.h"
#include "esp_err.h"

TimerHandle_t screensaver_timer = NULL;
bool screensaver_active = false;

void pxCallbackFunction(TimerHandle_t xTimer)
{
    // Code to activate the screensaver goes here
    screensaver_active = true;
    bsp_display_sleep();
}

esp_err_t screensaver_init(int idle_time_sec)
{

    esp_err_t err_t;

    screensaver_timer = xTimerCreate("ScreensaverTimer",
                                     pdMS_TO_TICKS(idle_time_sec * 1000),
                                     pdFALSE,
                                     (void *)0,
                                     pxCallbackFunction);

    if (screensaver_timer == NULL)
    {
        ESP_LOGE("screensaver", "Failed to create screensaver timer");
        return ESP_FAIL;
    }

    err_t = xTimerStart(screensaver_timer, 3);
    return err_t;
}

void screensaver_reset()
{
    esp_err_t err_t;
    if (screensaver_timer != NULL)
    {
        err_t = xTimerReset(screensaver_timer, 0);
        if (err_t != pdPASS)
        {
            ESP_LOGE("screensaver", "Screensaver timer reset with error code: %d", err_t);
        }
    }
    if (screensaver_active)
    {
        bsp_display_wake();
    }
    screensaver_active = false;
}
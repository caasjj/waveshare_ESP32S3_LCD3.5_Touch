#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "screensaver.h"
#include "esp_log.h"
#include "esp_err.h"

TimerHandle_t screensaver_timer = NULL;
bool screensaver_active = false;
esp_err_t (*screensleep_callback)(void) = NULL;
esp_err_t (*screenwake_callback)(void) = NULL;

void pxCallbackFunction(TimerHandle_t xTimer)
{
    // Code to activate the screensaver goes here
    screensaver_active = true;
    if (screensleep_callback != NULL)
    {
        ESP_ERROR_CHECK(screensleep_callback());
    }
}

esp_err_t screensaver_init(int idle_time_sec, esp_err_t (*screensleep_ptr)(void), esp_err_t (*screenwake_ptr)(void))
{

    esp_err_t err_t;

    screensleep_callback = screensleep_ptr;
    screenwake_callback = screenwake_ptr;
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
    if (screensaver_active && screenwake_callback != NULL)
    {
        ESP_ERROR_CHECK(screenwake_callback());
    }
    screensaver_active = false;
}
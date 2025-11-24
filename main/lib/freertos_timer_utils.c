#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void monitor_timer_task_stack_watermark(void)
{
    TaskHandle_t timer_task = xTimerGetTimerDaemonTaskHandle();
    if (timer_task != NULL)
    {
        UBaseType_t high_water_mark = uxTaskGetStackHighWaterMark(timer_task);
        printf("Timer task minimum free stack: %u words\n", (unsigned)high_water_mark);
    }
}
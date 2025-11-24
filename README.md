# Waveshare ESP32S3 3.5" Touch LCD Board Template
This is a template (based on [tsebelev](https://github.com/tsebelev/esp32_JC3248W535EN_work_exampl_lvgl_axs15231b)) for initializing the LCD and Touch interface, and implementing a screensaver for Waveshare's 3.5" LCD Touch module. See `/board_info` for details of this board.

*FreeRTOS software timer is used as the screensaver timer. The selected default value of `3584` allows for roughly 20% margin in the high watermark. Set `CONFIG_TIMER_TASK_STACK_MONITORING` to enable monitoring the timer watermark in the main loop.*
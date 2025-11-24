# Waveshare ESP32S3 3.5" Touch LCD Board Template
This is a template (based on [tsebelev](https://github.com/tsebelev/esp32_JC3248W535EN_work_exampl_lvgl_axs15231b)) for initializing the LCD and Touch interface, and implementing a screensaver for Waveshare's 3.5" LCD Touch module. See `/board_info` for details of this board.

The template screen implemented in `screens/template` is meant as a simple placeholder to confirm correct function of LCD and touch interface. This screen is meant to be removed and replaced with application specific screens.

The screensaver is implemented as a FreeRTOS software timer to activate, and a listener on the touch input directly, independent of the UI component, to de-activate. See `screensaver.c` for the screensaver, and `lib/touch_diplay.c` for the wake up from screensaver.

- *The FreeRTOS software timer stack size default value of `3584` allows for roughly 20% margin in the high watermark. Set `CONFIG_TIMER_TASK_STACK_MONITORING` to enable monitoring the timer watermark in the main loop.*
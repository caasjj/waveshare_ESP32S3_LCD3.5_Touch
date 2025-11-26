#ifndef SCREENSAVER_H
#define SCREENSAVER_H
#include <stdint.h>

esp_err_t screensaver_init(int idle_time_sec, esp_err_t (*screensleep_ptr)(void), esp_err_t (*screenwake_ptr)(void));
void screensaver_reset();

#endif // SCREENSAVER_H
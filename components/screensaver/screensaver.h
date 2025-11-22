#ifndef SCREENSAVER_H
#define SCREENSAVER_H
#include <stdint.h>

esp_err_t screensaver_init(int idle_time_sec);
void screensaver_reset();

#endif // SCREENSAVER_H
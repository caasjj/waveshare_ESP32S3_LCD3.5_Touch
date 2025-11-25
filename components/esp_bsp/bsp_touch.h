#ifndef BSP_TOUCH_H
#define BSP_TOUCH_H

#include "bsp_axs15231b.h"
#include "esp_lcd_axs15231b.h"
#include "esp_lvgl_port.h"

#define LCD_PIN_NUM_QSPI_TOUCH_SCL (GPIO_NUM_7)
#define LCD_PIN_NUM_QSPI_TOUCH_SDA (GPIO_NUM_8)
#define LCD_PIN_NUM_QSPI_TOUCH_RST (-1)
#define LCD_PIN_NUM_QSPI_TOUCH_INT (-1)

lv_indev_t *AXS15231B_touch_init(lv_display_t *lvgl_disp);
lv_indev_t *LVGL_touch_add(lv_display_t *lvgl_disp);
#endif
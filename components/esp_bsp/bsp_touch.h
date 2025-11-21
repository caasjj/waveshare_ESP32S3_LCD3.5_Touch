#ifndef BSP_TOUCH_H
#define BSP_TOUCH_H

#include "bsp_axs15231b.h"
#include "esp_lcd_axs15231b.h"
#include "esp_lvgl_port.h"

#define LCD_PIN_NUM_QSPI_TOUCH_SCL (GPIO_NUM_7)
#define LCD_PIN_NUM_QSPI_TOUCH_SDA (GPIO_NUM_8)
#define LCD_PIN_NUM_QSPI_TOUCH_RST (-1)
#define LCD_PIN_NUM_QSPI_TOUCH_INT (-1)

void touch_i2c_init(void);
void Initialize_AXS15231B_Touch(void);
lv_indev_t *Add_LVGL_Touch(lv_display_t *lvgl_disp);
#endif
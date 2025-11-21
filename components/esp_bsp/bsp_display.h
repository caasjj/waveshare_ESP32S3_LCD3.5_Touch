#ifndef BSP_DISPLAY_H
#define BSP_DISPLAY_H
#include "driver/ledc.h"
#include "esp_lcd_axs15231b.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_io_interface.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_panel_vendor.h"
#include "bsp_axs15231b.h"
#include "esp_lvgl_port.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// LCD spec of QSPI /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LCD_LEDC_CH 1

#define LCD_PIN_NUM_QSPI_CS (GPIO_NUM_12)
#define LCD_PIN_NUM_QSPI_PCLK (GPIO_NUM_5)
#define LCD_PIN_NUM_QSPI_DATA0 (GPIO_NUM_1)
#define LCD_PIN_NUM_QSPI_DATA1 (GPIO_NUM_2)
#define LCD_PIN_NUM_QSPI_DATA2 (GPIO_NUM_3)
#define LCD_PIN_NUM_QSPI_DATA3 (GPIO_NUM_4)
#define LCD_PIN_NUM_QSPI_RST (GPIO_NUM_NC)
#define LCD_PIN_NUM_QSPI_DC (GPIO_NUM_8)
#define LCD_PIN_NUM_QSPI_TE (GPIO_NUM_38)
#define LCD_PIN_NUM_QSPI_BL (GPIO_NUM_6)

///////////////////*************//////////////////////////////////// */

/* Hardware Config */
// #define LCD_HOST SPI2_HOST                            // LCD host is SPI2
// #define EXAMPLE_LCD_PIXEL_CLOCK_HZ (40 * 1000 * 1000) // SPI Clock Frequency is 40MHz
// #define EXAMPLE_LCD_BK_LIGHT_ON_LEVEL 1               // Backlight ON level
// #define EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL !EXAMPLE_LCD_BK_LIGHT_ON_LEVEL

////////////////////////////

////////////////////////////
/* LCD settings */
// #define LCD_DRAW_BUFF_HEIGHT (60)

#define DISPLAY_MIRROR_X false
#define DISPLAY_MIRROR_Y false
#define DISPLAY_SWAP_XY false
#define DISPLAY_INVERT_COLOR false

extern esp_lcd_panel_io_handle_t io_handle_lcd;
esp_err_t bsp_display_brightness_init(void);
esp_err_t bsp_display_brightness_set(int brightness_percent);
void AXS15231B_display_init(void);
lv_display_t *LVGL_display_add(void);
#endif
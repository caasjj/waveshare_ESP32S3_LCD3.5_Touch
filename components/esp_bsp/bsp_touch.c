#include "bsp_touch.h"
#include "esp_log.h"

#include "driver/i2c.h"
#include "esp_lcd_touch.h"

#include "esp_err.h"

static const char *TAG = "bsp_touch_axs15231b";
static esp_lcd_touch_handle_t touch_handle = NULL;
static lv_indev_t *lvgl_touch_indev = NULL;

void touch_i2c_init(void)
{
    const i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = LCD_PIN_NUM_QSPI_TOUCH_SDA,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = LCD_PIN_NUM_QSPI_TOUCH_SCL,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = BSP_I2C_CLK_SPEED_HZ};
    ESP_ERROR_CHECK(i2c_param_config(BSP_I2C_NUM, &i2c_conf));
    ESP_ERROR_CHECK(i2c_driver_install(BSP_I2C_NUM, i2c_conf.mode, 0, 0, 0));
}

void Initialize_AXS15231B_Touch()
{
    esp_lcd_touch_config_t tp_cfg = {
        .x_max = LCD_QSPI_H_RES,
        .y_max = LCD_QSPI_V_RES,
        .rst_gpio_num = LCD_PIN_NUM_QSPI_TOUCH_RST,
        .int_gpio_num = LCD_PIN_NUM_QSPI_TOUCH_INT,
        .levels = {
            .reset = 0,
            .interrupt = 0,
        },
        .flags = {
            .swap_xy = 0,
            .mirror_x = 0,
            .mirror_y = 0,
        },
    };
    const esp_lcd_panel_io_i2c_config_t tp_io_config = ESP_LCD_TOUCH_IO_I2C_AXS15231B_CONFIG();
    esp_lcd_panel_io_handle_t tp_io_handle = NULL;
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c((esp_lcd_i2c_bus_handle_t)BSP_I2C_NUM, &tp_io_config, &tp_io_handle));
    ESP_ERROR_CHECK(esp_lcd_touch_new_i2c_axs15231b(tp_io_handle, &tp_cfg, &touch_handle));
}

lv_indev_t *Add_LVGL_Touch(lv_display_t *lvgl_disp)
{
    const lvgl_port_touch_cfg_t touch_cfg = {
        .disp = lvgl_disp,
        .handle = touch_handle,
    };
    ESP_LOGI(TAG, "Adding touch input");
    lvgl_touch_indev = lvgl_port_add_touch(&touch_cfg);
    if (lvgl_touch_indev == NULL)
    {
        ESP_LOGE(TAG, "Failed to add LVGL touch input");
    }
    return lvgl_touch_indev;
}
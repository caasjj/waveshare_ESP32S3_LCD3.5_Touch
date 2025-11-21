file(GLOB_RECURSE SRC_FILES  "*.c" "*.cpp")

idf_component_register(SRCS ${SRC_FILES}
                    INCLUDE_DIRS "."
                    REQUIRES "driver" "esp_lcd_axs15231b" "esp_lvgl_port")
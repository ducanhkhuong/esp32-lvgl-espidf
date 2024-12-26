# Define the source files
file(GLOB_RECURSE SRC_FILES "*.c")
set(pre_req lvgl espressif__esp_lcd_gc9a01)
idf_component_register(
    SRCS ${SRC_FILES}
    INCLUDE_DIRS "."
    REQUIRES ${pre_req}
)

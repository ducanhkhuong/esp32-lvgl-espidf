
set(pre_req bt esp_wifi )

idf_component_register(
    SRCS "ble_server_lib.c"
    INCLUDE_DIRS "."
    REQUIRES ${pre_req})
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")

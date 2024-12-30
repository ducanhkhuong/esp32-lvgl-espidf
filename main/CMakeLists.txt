set(pri_req nvs_flash display gpio_lib timer_lib BLE_lib utils_lib)
idf_component_register(SRCS "main.c" 
                    INCLUDE_DIRS "."
                    REQUIRES ${pre_req})
set(pri_req driver)
idf_component_register(SRCS "gpio_config.c" 
                    INCLUDE_DIRS "."
                    REQUIRES ${pre_req})
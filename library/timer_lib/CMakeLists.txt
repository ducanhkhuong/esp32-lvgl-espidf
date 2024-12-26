set(pri_req nvs_flash driver)
idf_component_register(SRCS "systimer.c" 
                    INCLUDE_DIRS "."
                    REQUIRES ${pre_req})
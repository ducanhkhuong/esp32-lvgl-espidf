# Define the source files
file(GLOB_RECURSE SRC_FILES "*.c")
set(pre_req lvgl gc9a01_driver)
idf_component_register(
    SRCS ${SRC_FILES}
    INCLUDE_DIRS "."
    REQUIRES ${pre_req}
)

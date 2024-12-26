file(GLOB_RECURSE SRC_FILES "*.c")
file(GLOB_RECURSE IMG_SRC_FILES  "img/*.c")
file(GLOB_RECURSE FONT_SRC_FILES "font/*.c")

list(APPEND SRC_FILES ${IMG_SRC_FILES})
list(APPEND SRC_FILES ${FONT_SRC_FILES})

set(pre_req lvgl gc9a01_driver)

idf_component_register(
    SRCS ${SRC_FILES}
    INCLUDE_DIRS "." "img" "font"
    REQUIRES ${pre_req}
)


set(pre_req driver unity chmorgan__esp-audio-player spiffs)

idf_component_register(
    SRCS "speaker_ns4168.c" "sound.c"
    INCLUDE_DIRS "."    
    REQUIRES ${pre_req})

spiffs_create_partition_image(sound ../../spiff FLASH_IN_PROJECT)

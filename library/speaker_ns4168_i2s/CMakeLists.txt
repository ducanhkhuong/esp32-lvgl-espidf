
set(pre_req driver unity chmorgan__esp-audio-player )

idf_component_register(
    SRCS "speaker_ns4168.c"
    INCLUDE_DIRS "."
    REQUIRES ${pre_req}
    EMBED_TXTFILES 4.mp3)

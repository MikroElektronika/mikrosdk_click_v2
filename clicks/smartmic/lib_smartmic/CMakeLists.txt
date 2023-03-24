cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_smartmic LANGUAGES MikroC)
else()
    project(lib_smartmic LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_smartmic STATIC
        src/smartmic.c
        include/smartmic.h    include/resources/firmware_i2c.h    include/resources/firmware_spi.h    include/resources/firmware_uart.h    include/resources/system_config_6sec_to.h    include/resources/system_config_6sec_to_utk.h    include/resources/system_config_6sec_to_vid.h    include/resources/keyword_hello_voice_q2.h    include/resources/keyword_next_song.h    include/resources/keyword_switch_the_light.h    include/resources/keyword_baidu_yixia.h
)
add_library(Click.SmartMic  ALIAS lib_smartmic)

if (${MCU_NAME} MATCHES "(^PIC18F(.+)[KQ]4[23]$)|(^PIC32(.+)$)")
    set(sample_mode_reg_case "SAMPLE_REG_CASE_1")
else()
    set(sample_mode_reg_case "SAMPLE_REG_CASE_2")
endif()

target_compile_definitions(lib_smartmic PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_smartmic PUBLIC
        include    include/resources
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_smartmic PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_smartmic PUBLIC MikroSDK.Driver)

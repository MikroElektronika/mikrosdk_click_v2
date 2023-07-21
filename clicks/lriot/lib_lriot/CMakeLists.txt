cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lriot LANGUAGES MikroC)
else()
    project(lib_lriot LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lriot STATIC
        src/lriot.c
        src/driver/transceiver/lr1110_crypto_engine.c
        src/driver/transceiver/lr1110_driver_version.c
        src/driver/transceiver/lr1110_gnss.c
        src/driver/transceiver/lr1110_radio.c
        src/driver/transceiver/lr1110_radio_timings.c
        src/driver/transceiver/lr1110_regmem.c
        src/driver/transceiver/lr1110_system.c
        src/driver/transceiver/lr1110_wifi.c
        src/driver/transceiver/lr1110_lr_fhss.c
        src/driver/modem/lr1110_modem_hal.c
        src/driver/modem/lr1110_modem_driver_version.c
        src/driver/modem/lr1110_modem_gnss.c
        src/driver/modem/lr1110_modem_helper.c
        src/driver/modem/lr1110_modem_lorawan.c
        src/driver/modem/lr1110_modem_system.c
        src/driver/modem/lr1110_modem_wifi.c
        src/driver/common/lr1110_hal.c
        src/driver/common/lr1110_bootloader.c
        src/driver/firmware_update/lr1110_firmware_update.c
        include/lriot.h
        include/driver/transceiver/lr1110_crypto_engine.h
        include/driver/transceiver/lr1110_crypto_engine_types.h
        include/driver/transceiver/lr1110_driver_version.h
        include/driver/transceiver/lr1110_gnss.h
        include/driver/transceiver/lr1110_gnss_types.h
        include/driver/transceiver/lr1110_radio.h
        include/driver/transceiver/lr1110_radio_timings.h
        include/driver/transceiver/lr1110_radio_types.h
        include/driver/transceiver/lr1110_regmem.h
        include/driver/transceiver/lr1110_system.h
        include/driver/transceiver/lr1110_system_types.h
        include/driver/transceiver/lr1110_wifi.h
        include/driver/transceiver/lr1110_wifi_types.h
        include/driver/transceiver/lr_fhss_v1_base_types.h
        include/driver/transceiver/lr1110_lr_fhss.h
        include/driver/transceiver/lr1110_lr_fhss_types.h
        include/driver/modem/lr1110_modem_common.h
        include/driver/modem/lr1110_modem_driver_version.h
        include/driver/modem/lr1110_modem_gnss.h
        include/driver/modem/lr1110_modem_hal.h
        include/driver/modem/lr1110_modem_helper.h
        include/driver/modem/lr1110_modem_lorawan.h
        include/driver/modem/lr1110_modem_system.h
        include/driver/modem/lr1110_modem_wifi.h
        include/driver/common/lr1110_hal.h
        include/driver/common/lr1110_types.h
        include/driver/common/lr1110_bootloader.h
        include/driver/common/lr1110_bootloader_types.h
        include/driver/firmware_update/lr1110_firmware_update.h
        include/driver/firmware_update/lr1110_transceiver_0307.h
        include/driver/firmware_update/lr1110_modem_010107.h
        include/driver/modem/lr1110_modem_lorawan_types.h
        include/driver/modem/lr1110_modem_wifi_types.h
        include/driver/modem/lr1110_modem_gnss_types.h
        include/driver/modem/lr1110_modem_helper_types.h
        include/driver/modem/lr1110_modem_system_types.h
)
add_library(Click.LRIoT  ALIAS lib_lriot)

if (${CORE_NAME} MATCHES "DSPIC")
    if (${MCU_NAME} MATCHES "(^PIC24FV?(0[48]|16)K[ML][1234](.+)$)")
        set(sample_mode_reg_case "SAMPLE_REG_CASE_2")
    else()
        set(sample_mode_reg_case "SAMPLE_REG_CASE_1")
    endif()
else()
    if (${MCU_NAME} MATCHES "(^PIC18F(.+)[KQ]4[23]$)|(^PIC32(.+)$)")
        set(sample_mode_reg_case "SAMPLE_REG_CASE_1")
    else()
        set(sample_mode_reg_case "SAMPLE_REG_CASE_2")
    endif()
endif()

target_compile_definitions(lib_lriot PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_lriot PUBLIC
        include
        include/driver
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lriot PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lriot PUBLIC MikroSDK.Driver)

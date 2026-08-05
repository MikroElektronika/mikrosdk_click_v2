cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nfc9 LANGUAGES MikroC)
else()
    project(lib_nfc9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nfc9 STATIC
        src/nfc9.c
        src/nfc9_rfal.c
        include/nfc9.h
        include/nfc9_rfal.h
        include/rfal_platform.h
)
add_library(Click.NFC9 ALIAS lib_nfc9)

set(RFAL_CORE_SOURCES
        rfal/source/rfal_analogConfig.c
        rfal/source/rfal_crc.c
        rfal/source/rfal_iso15693_2.c
        rfal/source/rfal_nfc.c
        rfal/source/rfal_nfca.c
        rfal/source/rfal_nfcb.c
        rfal/source/rfal_nfcf.c
        rfal/source/rfal_nfcv.c
        rfal/source/st25r500/rfal_rfst25r500.c
        rfal/source/st25r500/st25r500.c
        rfal/source/st25r500/st25r500_com.c
        rfal/source/st25r500/st25r500_irq.c
)

target_sources(lib_nfc9 PRIVATE ${RFAL_CORE_SOURCES})

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

target_compile_definitions(lib_nfc9 PUBLIC ${sample_mode_reg_case} ST25R500 ST25R_POLL_IRQ)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    target_compile_definitions(lib_nfc9 PRIVATE data=rfal_data)
endif()

target_include_directories(lib_nfc9 PUBLIC
        include
        rfal/include
        rfal/source
        rfal/source/st25r500
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nfc9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nfc9 PUBLIC MikroSDK.Driver)

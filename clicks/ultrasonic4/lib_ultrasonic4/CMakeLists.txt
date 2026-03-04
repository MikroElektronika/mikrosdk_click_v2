cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ultrasonic4 LANGUAGES MikroC)
else()
    project(lib_ultrasonic4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ultrasonic4 STATIC
    src/ultrasonic4.c
    src/bsp.c
    include/ultrasonic4.h
    include/bsp.h
    include/app_config.h
)
add_library(Click.Ultrasonic4  ALIAS lib_ultrasonic4)

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

target_compile_definitions(lib_ultrasonic4 PUBLIC ${sample_mode_reg_case})


target_include_directories(lib_ultrasonic4 PUBLIC 
        include
)

set(CHIRP_MAX_NUM_SENSORS 1 CACHE STRING "one sensor connected" FORCE)
set(CHIRP_NUM_BUSES 1 CACHE STRING "one sensor connected" FORCE)
set(INCLUDE_SHASTA_SUPPORT ON CACHE BOOL "using ICU sensors" FORCE)
set(CHIRP_SENSOR_INT_PIN 1 CACHE STRING "use INT1 as interrupt" FORCE)
set(CHIRP_SENSOR_TRIG_PIN 1 CACHE STRING "use INT1 as trigger" FORCE)
set(CHIRP_MAIN_FW_TYPE "GPT" CACHE STRING "using fw icu_gpt" FORCE)
set(CHIRP_INIT_FW_TYPE "FULL" CACHE STRING "using fw icu_init" FORCE)
set(CHIRP_LOG_LEVEL 5 CACHE STRING "log=app" FORCE)
 
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/invn-soniclib)
target_link_libraries(lib_ultrasonic4 PRIVATE soniclib)
find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ultrasonic4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ultrasonic4 PUBLIC MikroSDK.Driver)


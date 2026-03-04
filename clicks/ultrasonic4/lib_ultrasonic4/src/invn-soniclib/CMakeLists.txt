cmake_minimum_required(VERSION 3.13)
set(PROJ_NAME soniclib)
project(SONICLIB C ASM)

set(CMAKE_C_STANDARD 99)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}) # needed to allow soniclib files to see relative include paths
set(SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/invn/soniclib)
set(SENS_FW_PATH ${CMAKE_CURRENT_SOURCE_DIR}/invn/soniclib/sensor_fw)
set(ICU_INTERFACE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/invn/icu_interface)

message(STATUS "")
message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
message(STATUS "")
message(STATUS "COMPILER FLAGS")
message(STATUS "==============")
message(STATUS "CMAKE_C_FLAGS=${CMAKE_C_FLAGS}")
message(STATUS "CMAKE_C_FLAGS_DEBUG=${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "CMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "CMAKE_C_FLAGS_RELWITHDEBINFO=${CMAKE_C_FLAGS_RELWITHDEBINFO}")
message(STATUS "CMAKE_C_FLAGS_MINSIZEREL=${CMAKE_C_FLAGS_MINSIZEREL}")
message(STATUS "")
message(STATUS "CMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")

set(CHIRP_MAX_NUM_SENSORS 4 CACHE STRING "Max number of supported sensors.")
set(CHIRP_NUM_BUSES 2 CACHE STRING "Number of I2C/SPI buses used by sensors.")
set(INCLUDE_SHASTA_SUPPORT OFF CACHE BOOL
        "Build soniclib for shasta (ICU) targets. Default is whitney targets \
        (chx01).")
set(CHIRP_SENSOR_INT_PIN 1 CACHE STRING "Pin used for interrupts (shasta only).")
set(CHIRP_SENSOR_TRIG_PIN 1 CACHE STRING "Pin used for triggers (shasta only).")
set(CHIRP_INIT_FW_TYPE "FULL" CACHE STRING
        "Type of init firmware (shasta only). NO_TX_OPTIMIZATION leaves out the \
        transmit optimization feature but saves some space. NONE means no init \
        firmware. Not all firmware variants support the NONE option.")
set_property(CACHE CHIRP_INIT_FW_TYPE PROPERTY STRINGS FULL
                                                        NO_TX_OPTIMIZATION
                                                        NONE)
set(CHIRP_MAIN_FW_TYPE "NONE" CACHE STRING
        "Main firmware to embed (if using one of the fw supplied with Soniclib)\
        Can be one of the follwing : NONE (build with another fw),\
        GPT, CH101_GPR, CH201_GPRMT, CHX01_FREQSWEEP")
set_property(CACHE CHIRP_MAIN_FW_TYPE PROPERTY STRINGS NONE, GPT,
                                                        CH101_GPR, CH201_GPRMT,
                                                        CHX01_FREQSWEEP)
set(INCLUDE_ALGO_EXTERNAL ON CACHE BOOL
        "If set, do not include gpt (rangefinder) support (deprecated)")
set(CHIRP_LOG_LEVEL 4 CACHE STRING
        "Define the log level to use for the Soniclib internal log messages \
        (4 = CH_LOG_LEVEL_ERROR)")
set(RUN_UNIT_TEST OFF CACHE BOOL "If set, compile and run unit tests.")

if(RUN_UNIT_TEST)
  set(CMAKE_C_FLAGS --coverage)
  set(GCOV_LINK_FLAGS "--coverage")
endif()

message(STATUS "CHIRP_MAX_NUM_SENSORS=${CHIRP_MAX_NUM_SENSORS}")
message(STATUS "CHIRP_NUM_BUSES=${CHIRP_NUM_BUSES}")
message(STATUS "CHIRP_SENSOR_INT_PIN=${CHIRP_SENSOR_INT_PIN}")
message(STATUS "CHIRP_SENSOR_TRIG_PIN=${CHIRP_SENSOR_TRIG_PIN}")

message(STATUS "CHIRP_INIT_FW_TYPE=${CHIRP_INIT_FW_TYPE}")
message(STATUS "CHIRP_MAIN_FW_TYPE=${CHIRP_MAIN_FW_TYPE}")
message(STATUS "INCLUDE_ALGO_EXTERNAL=${INCLUDE_ALGO_EXTERNAL}")
message(STATUS "INCLUDE_SHASTA_SUPPORT=${INCLUDE_SHASTA_SUPPORT}")
message(STATUS "CHIRP_LOG_LEVEL=${CHIRP_LOG_LEVEL}")
message(STATUS "RUN_UNIT_TEST=${RUN_UNIT_TEST}")

set(SOURCES ${SRC_PATH}/chbsp_dummy.c
            ${SRC_PATH}/ch_api.c
            ${SRC_PATH}/ch_common.c
            ${SRC_PATH}/ch_driver.c
            ${SRC_PATH}/ch_math_utils.c)

if (NOT ${CHIRP_LOG_LEVEL} EQUAL 6)
# Build ch_log module if CHIRP_LOG_LEVEL isn't CH_LOG_LEVEL_DISABLE
set(SOURCES ${SOURCES}
            ${SRC_PATH}/ch_log.c
            ${SRC_PATH}/extra/ch_extra_display_utils.c)
endif()

if(INCLUDE_SHASTA_SUPPORT)
    if (CHIRP_MAIN_FW_TYPE STREQUAL "GPT" OR NOT INCLUDE_ALGO_EXTERNAL)
        set(SOURCES ${SOURCES}
                    ${SENS_FW_PATH}/icu_gpt/icu_gpt.c
                    ${SENS_FW_PATH}/icu_gpt/icu_gpt_fw.c)
    endif()
    if (CHIRP_INIT_FW_TYPE STREQUAL "FULL")
        set(SOURCES ${SOURCES}
                    ${SENS_FW_PATH}/icu_init/icu_init.c
                    ${SENS_FW_PATH}/icu_init/icu_init_fw.c)
    endif()
    if (CHIRP_INIT_FW_TYPE STREQUAL "NO_TX_OPTIMIZATION")
        set(SOURCES ${SOURCES}
                    ${SENS_FW_PATH}/icu_init-no-txopt/icu_init-no-txopt.c
                    ${SENS_FW_PATH}/icu_init-no-txopt/icu_init-no-txopt_fw.c)
    endif()
else()
    set(SOURCES ${SOURCES}
                ${SRC_PATH}/ch_rangefinder.c)
    if (CHIRP_MAIN_FW_TYPE STREQUAL "CH101_GPR")
        set(SOURCES ${SOURCES}
                ${SENS_FW_PATH}/ch101/ch101_gpr.c
                ${SENS_FW_PATH}/ch101/ch101_gpr_fw.c)
    endif()
    if (CHIRP_MAIN_FW_TYPE STREQUAL "CH201_GPRMT")
        set(SOURCES ${SOURCES}
                ${SENS_FW_PATH}/ch201/ch201_gprmt.c
                ${SENS_FW_PATH}/ch201/ch201_gprmt_fw.c)
    endif()
    if (CHIRP_MAIN_FW_TYPE STREQUAL "CHX01_FREQSWEEP")
        set(SOURCES ${SOURCES}
                ${SENS_FW_PATH}/chx01/chx01_freqsweep.c
                ${SENS_FW_PATH}/chx01/chx01_freqsweep_fw.c)
    endif()
endif()

add_library(${PROJ_NAME} STATIC ${SOURCES})

target_include_directories(${PROJ_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(${PROJ_NAME}
    PUBLIC -DINVN_SONICLIB_INTERNAL_BOARD_CONFIG
            -DCHIRP_MAX_NUM_SENSORS=${CHIRP_MAX_NUM_SENSORS}
            -DCHIRP_NUM_BUSES=${CHIRP_NUM_BUSES}
            -DCH_LOG_MODULE_LEVEL=${CHIRP_LOG_LEVEL})

if(INCLUDE_SHASTA_SUPPORT)
    target_compile_definitions(${PROJ_NAME} PUBLIC -DINCLUDE_SHASTA_SUPPORT
        PUBLIC -DCHIRP_SENSOR_INT_PIN=${CHIRP_SENSOR_INT_PIN}
                -DCHIRP_SENSOR_TRIG_PIN=${CHIRP_SENSOR_TRIG_PIN})
else()
    target_compile_definitions(${PROJ_NAME} PUBLIC -DINCLUDE_WHITNEY_SUPPORT)
endif()

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
        DESTINATION ${CMAKE_SOURCE_DIR})

if(RUN_UNIT_TEST)
  add_compile_options(-g -O0 --coverage)
  add_link_options("--coverage")
  add_subdirectory(test/unit_test)
endif()

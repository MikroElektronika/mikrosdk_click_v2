cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rtc16 LANGUAGES MikroC)
else()
    project(example_rtc16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rtc16
        main.c

)


############################ example_rtc16 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rtc16 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rtc16 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rtc16 PUBLIC MikroSDK.Log)
add_subdirectory(lib_rtc16)
target_link_libraries(example_rtc16 PUBLIC Click.RTC16)
############################ example_rtc16 GENERATED CODE END ###########################

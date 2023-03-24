cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rtc17 LANGUAGES MikroC)
else()
    project(example_rtc17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rtc17
        main.c

)


############################ example_rtc17 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rtc17 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rtc17 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rtc17 PUBLIC MikroSDK.Log)
add_subdirectory(lib_rtc17)
target_link_libraries(example_rtc17 PUBLIC Click.RTC17)
############################ example_rtc17 GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rtc19 LANGUAGES MikroC)
else()
    project(example_rtc19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rtc19
        main.c

)


############################ example_rtc19 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rtc19 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rtc19 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rtc19 PUBLIC MikroSDK.Log)
add_subdirectory(lib_rtc19)
target_link_libraries(example_rtc19 PUBLIC Click.RTC19)
############################ example_rtc19 GENERATED CODE END ###########################

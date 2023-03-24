cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_powermonitor LANGUAGES MikroC)
else()
    project(example_powermonitor LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_powermonitor
        main.c

)


############################ example_powermonitor GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_powermonitor PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_powermonitor PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_powermonitor PUBLIC MikroSDK.Log)
add_subdirectory(lib_powermonitor)
target_link_libraries(example_powermonitor PUBLIC Click.PowerMonitor)
############################ example_powermonitor GENERATED CODE END ###########################

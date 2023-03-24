cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_oledswitch LANGUAGES MikroC)
else()
    project(example_oledswitch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_oledswitch
        main.c

)


############################ example_oledswitch GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_oledswitch PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_oledswitch PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_oledswitch PUBLIC MikroSDK.Log)
add_subdirectory(lib_oledswitch)
target_link_libraries(example_oledswitch PUBLIC Click.OledSwitch)
############################ example_oledswitch GENERATED CODE END ###########################

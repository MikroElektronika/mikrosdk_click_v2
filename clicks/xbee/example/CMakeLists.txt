cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_xbee LANGUAGES MikroC)
else()
    project(example_xbee LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_xbee
        main.c

)


############################ example_xbee GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_xbee PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_xbee PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_xbee PUBLIC MikroSDK.Log)
add_subdirectory(lib_xbee)
target_link_libraries(example_xbee PUBLIC Click.XBEE)
############################ example_xbee GENERATED CODE END ###########################

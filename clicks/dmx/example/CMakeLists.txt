cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_dmx LANGUAGES MikroC)
else()
    project(example_dmx LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_dmx
        main.c

)


############################ example_dmx GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_dmx PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_dmx PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_dmx PUBLIC MikroSDK.Log)
add_subdirectory(lib_dmx)
target_link_libraries(example_dmx PUBLIC Click.Dmx)
############################ example_dmx GENERATED CODE END ###########################

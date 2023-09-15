cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_osd LANGUAGES MikroC)
else()
    project(example_osd LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_osd
        main.c

)


############################ example_osd GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_osd PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_osd PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_osd PUBLIC MikroSDK.Log)
add_subdirectory(lib_osd)
target_link_libraries(example_osd PUBLIC Click.OSD)
############################ example_osd GENERATED CODE END ###########################

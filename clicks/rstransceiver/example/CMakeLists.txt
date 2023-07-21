cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rstransceiver LANGUAGES MikroC)
else()
    project(example_rstransceiver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rstransceiver
        main.c
    
)


############################ example_rstransceiver GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rstransceiver PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rstransceiver PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rstransceiver PUBLIC MikroSDK.Log)
add_subdirectory(lib_rstransceiver)
target_link_libraries(example_rstransceiver PUBLIC Click.RSTransceiver)
############################ example_rstransceiver GENERATED CODE END ###########################


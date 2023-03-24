cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_btez LANGUAGES MikroC)
else()
    project(example_btez LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_btez
        main.c

)


############################ example_btez GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_btez PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_btez PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_btez PUBLIC MikroSDK.Log)
add_subdirectory(lib_btez)
target_link_libraries(example_btez PUBLIC Click.BtEz)
############################ example_btez GENERATED CODE END ###########################

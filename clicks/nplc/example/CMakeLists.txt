cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_nplc LANGUAGES MikroC)
else()
    project(example_nplc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_nplc
        main.c
    
)


############################ example_nplc GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_nplc PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_nplc PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_nplc PUBLIC MikroSDK.Log)
add_subdirectory(lib_nplc)
target_link_libraries(example_nplc PUBLIC Click.NPLC)
############################ example_nplc GENERATED CODE END ###########################


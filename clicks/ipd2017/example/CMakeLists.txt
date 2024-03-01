cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ipd2017 LANGUAGES MikroC)
else()
    project(example_ipd2017 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ipd2017
        main.c
    
)


############################ example_ipd2017 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ipd2017 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ipd2017 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ipd2017 PUBLIC MikroSDK.Log)
add_subdirectory(lib_ipd2017)
target_link_libraries(example_ipd2017 PUBLIC Click.IPD2017)
############################ example_ipd2017 GENERATED CODE END ###########################


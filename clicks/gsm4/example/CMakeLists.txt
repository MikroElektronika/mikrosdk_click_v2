cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gsm4 LANGUAGES MikroC)
else()
    project(example_gsm4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gsm4
        main.c

)


############################ example_gsm4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gsm4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gsm4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gsm4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_gsm4)
target_link_libraries(example_gsm4 PUBLIC Click.GSM4)
############################ example_gsm4 GENERATED CODE END ###########################

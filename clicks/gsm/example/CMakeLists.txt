cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gsm LANGUAGES MikroC)
else()
    project(example_gsm LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gsm
        main.c

)


############################ example_gsm GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gsm PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gsm PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gsm PUBLIC MikroSDK.Log)
add_subdirectory(lib_gsm)
target_link_libraries(example_gsm PUBLIC Click.GSM)
############################ example_gsm GENERATED CODE END ###########################

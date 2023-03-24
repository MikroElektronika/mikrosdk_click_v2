cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rmstodc LANGUAGES MikroC)
else()
    project(example_rmstodc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rmstodc
        example/main.c

)


############################ example_rmstodc GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rmstodc PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rmstodc PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rmstodc PUBLIC MikroSDK.Log)
add_subdirectory(lib_rmstodc)
target_link_libraries(example_rmstodc PUBLIC Click.RmstoDc)
############################ example_rmstodc GENERATED CODE END ###########################

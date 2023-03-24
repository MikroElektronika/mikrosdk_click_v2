cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_dsp LANGUAGES MikroC)
else()
    project(example_dsp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_dsp
        example/main.c

)


############################ example_dsp GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_dsp PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_dsp PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_dsp PUBLIC MikroSDK.Log)
add_subdirectory(lib_dsp)
target_link_libraries(example_dsp PUBLIC Click.Dsp)
############################ example_dsp GENERATED CODE END ###########################

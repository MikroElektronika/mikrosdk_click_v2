cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mic33153 LANGUAGES MikroC)
else()
    project(example_mic33153 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mic33153
        example/main.c

)


############################ example_mic33153 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mic33153 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mic33153 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mic33153 PUBLIC MikroSDK.Log)
add_subdirectory(lib_mic33153)
target_link_libraries(example_mic33153 PUBLIC Click.Mic33153)
############################ example_mic33153 GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_audioamp4 LANGUAGES MikroC)
else()
    project(example_audioamp4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_audioamp4
        example/main.c

)


############################ example_audioamp4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_audioamp4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_audioamp4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_audioamp4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_audioamp4)
target_link_libraries(example_audioamp4 PUBLIC Click.AudioAmp4)
############################ example_audioamp4 GENERATED CODE END ###########################

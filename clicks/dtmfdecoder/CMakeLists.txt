cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_dtmfdecoder LANGUAGES MikroC)
else()
    project(example_dtmfdecoder LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_dtmfdecoder
        example/main.c

)


############################ example_dtmfdecoder GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_dtmfdecoder PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_dtmfdecoder PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_dtmfdecoder PUBLIC MikroSDK.Log)
add_subdirectory(lib_dtmfdecoder)
target_link_libraries(example_dtmfdecoder PUBLIC Click.DTMFDecoder)
############################ example_dtmfdecoder GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_btaudio LANGUAGES MikroC)
else()
    project(example_btaudio LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_btaudio
        main.c

)


############################ example_btaudio GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_btaudio PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_btaudio PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_btaudio PUBLIC MikroSDK.Log)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(example_btaudio PUBLIC MikroSDK.GenericPointer)
add_subdirectory(lib_btaudio)
target_link_libraries(example_btaudio PUBLIC Click.BtAudio)
############################ example_btaudio GENERATED CODE END ###########################

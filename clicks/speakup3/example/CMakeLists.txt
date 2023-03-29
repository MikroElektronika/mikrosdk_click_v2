cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_speakup3 LANGUAGES MikroC)
else()
    project(example_speakup3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_speakup3
        main.c

)


############################ example_speakup3 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_speakup3 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_speakup3 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_speakup3 PUBLIC MikroSDK.Log)
add_subdirectory(lib_speakup3)
target_link_libraries(example_speakup3 PUBLIC Click.SpeakUp3)
############################ example_speakup3 GENERATED CODE END ###########################

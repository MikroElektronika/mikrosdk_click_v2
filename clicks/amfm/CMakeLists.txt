cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_amfm LANGUAGES MikroC)
else()
    project(example_amfm LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_amfm
        example/main.c

)


############################ example_amfm GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_amfm PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_amfm PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_amfm PUBLIC MikroSDK.Log)
add_subdirectory(lib_amfm)
target_link_libraries(example_amfm PUBLIC Click.AmFm)
############################ example_amfm GENERATED CODE END ###########################

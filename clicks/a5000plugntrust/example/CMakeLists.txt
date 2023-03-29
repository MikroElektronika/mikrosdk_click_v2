cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_a5000plugntrust LANGUAGES MikroC)
else()
    project(example_a5000plugntrust LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_a5000plugntrust
        main.c

)


############################ example_a5000plugntrust GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_a5000plugntrust PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_a5000plugntrust PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_a5000plugntrust PUBLIC MikroSDK.Log)
add_subdirectory(lib_a5000plugntrust)
target_link_libraries(example_a5000plugntrust PUBLIC Click.A5000PlugnTrust)
############################ example_a5000plugntrust GENERATED CODE END ###########################

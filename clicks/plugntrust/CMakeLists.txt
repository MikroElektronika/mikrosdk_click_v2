cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_plugntrust LANGUAGES MikroC)
else()
    project(example_plugntrust LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_plugntrust
        example/main.c

)


############################ example_plugntrust GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_plugntrust PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_plugntrust PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_plugntrust PUBLIC MikroSDK.Log)
add_subdirectory(lib_plugntrust)
target_link_libraries(example_plugntrust PUBLIC Click.PlugnTrust)
############################ example_plugntrust GENERATED CODE END ###########################

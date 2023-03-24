cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_thumbwheel LANGUAGES MikroC)
else()
    project(example_thumbwheel LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_thumbwheel
        main.c

)


############################ example_thumbwheel GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_thumbwheel PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_thumbwheel PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_thumbwheel PUBLIC MikroSDK.Log)
add_subdirectory(lib_thumbwheel)
target_link_libraries(example_thumbwheel PUBLIC Click.Thumbwheel)
############################ example_thumbwheel GENERATED CODE END ###########################

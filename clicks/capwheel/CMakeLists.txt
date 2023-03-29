cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_capwheel LANGUAGES MikroC)
else()
    project(example_capwheel LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_capwheel
        example/main.c

)


############################ example_capwheel GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_capwheel PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_capwheel PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_capwheel PUBLIC MikroSDK.Log)
add_subdirectory(lib_capwheel)
target_link_libraries(example_capwheel PUBLIC Click.CapWheel)
############################ example_capwheel GENERATED CODE END ###########################

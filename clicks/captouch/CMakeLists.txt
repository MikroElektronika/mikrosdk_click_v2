cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_captouch LANGUAGES MikroC)
else()
    project(example_captouch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_captouch
        example/main.c

)


############################ example_captouch GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_captouch PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_captouch PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_captouch PUBLIC MikroSDK.Log)
add_subdirectory(lib_captouch)
target_link_libraries(example_captouch PUBLIC Click.CapTouch)
############################ example_captouch GENERATED CODE END ###########################

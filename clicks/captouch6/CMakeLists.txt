cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_captouch6 LANGUAGES MikroC)
else()
    project(example_captouch6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_captouch6
        example/main.c

)


############################ example_captouch6 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_captouch6 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_captouch6 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_captouch6 PUBLIC MikroSDK.Log)
add_subdirectory(lib_captouch6)
target_link_libraries(example_captouch6 PUBLIC Click.CapTouch6)
############################ example_captouch6 GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_captouch5 LANGUAGES MikroC)
else()
    project(example_captouch5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_captouch5
        example/main.c

)


############################ example_captouch5 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_captouch5 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_captouch5 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_captouch5 PUBLIC MikroSDK.Log)
add_subdirectory(lib_captouch5)
target_link_libraries(example_captouch5 PUBLIC Click.CapTouch5)
############################ example_captouch5 GENERATED CODE END ###########################

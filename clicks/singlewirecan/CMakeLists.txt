cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_singlewirecan LANGUAGES MikroC)
else()
    project(example_singlewirecan LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_singlewirecan
        example/main.c

)


############################ example_singlewirecan GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_singlewirecan PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_singlewirecan PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_singlewirecan PUBLIC MikroSDK.Log)
add_subdirectory(lib_singlewirecan)
target_link_libraries(example_singlewirecan PUBLIC Click.SingleWireCan)
############################ example_singlewirecan GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_capextend LANGUAGES MikroC)
else()
    project(example_capextend LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_capextend
        main.c

)


############################ example_capextend GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_capextend PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_capextend PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_capextend PUBLIC MikroSDK.Log)
add_subdirectory(lib_capextend)
target_link_libraries(example_capextend PUBLIC Click.CapExtend)
############################ example_capextend GENERATED CODE END ###########################

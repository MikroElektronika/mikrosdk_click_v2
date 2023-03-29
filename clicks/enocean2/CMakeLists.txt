cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_enocean2 LANGUAGES MikroC)
else()
    project(example_enocean2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_enocean2
        example/main.c

)


############################ example_enocean2 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_enocean2 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_enocean2 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_enocean2 PUBLIC MikroSDK.Log)
add_subdirectory(lib_enocean2)
target_link_libraries(example_enocean2 PUBLIC Click.EnOcean2)
############################ example_enocean2 GENERATED CODE END ###########################

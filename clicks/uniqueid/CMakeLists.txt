cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_uniqueid LANGUAGES MikroC)
else()
    project(example_uniqueid LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_uniqueid
        example/main.c

)


############################ example_uniqueid GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_uniqueid PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_uniqueid PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_uniqueid PUBLIC MikroSDK.Log)
add_subdirectory(lib_uniqueid)
target_link_libraries(example_uniqueid PUBLIC Click.UNIQUEID)
############################ example_uniqueid GENERATED CODE END ###########################

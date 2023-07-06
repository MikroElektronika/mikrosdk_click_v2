cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_thingstream LANGUAGES MikroC)
else()
    project(example_thingstream LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_thingstream
        example/main.c

)


############################ example_thingstream GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_thingstream PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_thingstream PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_thingstream PUBLIC MikroSDK.Log)
add_subdirectory(lib_thingstream)
target_link_libraries(example_thingstream PUBLIC Click.Thingstream)
############################ example_thingstream GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_humidity LANGUAGES MikroC)
else()
    project(example_humidity LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_humidity
        example/main.c

)


############################ example_humidity GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_humidity PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_humidity PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_humidity PUBLIC MikroSDK.Log)
add_subdirectory(lib_humidity)
target_link_libraries(example_humidity PUBLIC Click.Humidity)
############################ example_humidity GENERATED CODE END ###########################

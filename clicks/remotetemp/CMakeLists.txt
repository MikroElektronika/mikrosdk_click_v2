cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_remotetemp LANGUAGES MikroC)
else()
    project(example_remotetemp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_remotetemp
        example/main.c

)


############################ example_remotetemp GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_remotetemp PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_remotetemp PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_remotetemp PUBLIC MikroSDK.Log)
add_subdirectory(lib_remotetemp)
target_link_libraries(example_remotetemp PUBLIC Click.RemoteTemp)
############################ example_remotetemp GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ammeter LANGUAGES MikroC)
else()
    project(example_ammeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ammeter
        example/main.c

)


############################ example_ammeter GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ammeter PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ammeter PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ammeter PUBLIC MikroSDK.Log)
add_subdirectory(lib_ammeter)
target_link_libraries(example_ammeter PUBLIC Click.Ammeter)
############################ example_ammeter GENERATED CODE END ###########################

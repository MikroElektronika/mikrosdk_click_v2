cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_irreflect LANGUAGES MikroC)
else()
    project(example_irreflect LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_irreflect
        main.c

)


############################ example_irreflect GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_irreflect PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_irreflect PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_irreflect PUBLIC MikroSDK.Log)
add_subdirectory(lib_irreflect)
target_link_libraries(example_irreflect PUBLIC Click.IrReflect)
############################ example_irreflect GENERATED CODE END ###########################

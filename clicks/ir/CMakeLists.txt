cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ir LANGUAGES MikroC)
else()
    project(example_ir LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ir
        example/main.c

)


############################ example_ir GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ir PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ir PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ir PUBLIC MikroSDK.Log)
add_subdirectory(lib_ir)
target_link_libraries(example_ir PUBLIC Click.IR)
############################ example_ir GENERATED CODE END ###########################

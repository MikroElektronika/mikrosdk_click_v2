cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rmeter LANGUAGES MikroC)
else()
    project(example_rmeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rmeter
        example/main.c

)


############################ example_rmeter GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rmeter PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rmeter PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rmeter PUBLIC MikroSDK.Log)
add_subdirectory(lib_rmeter)
target_link_libraries(example_rmeter PUBLIC Click.Rmeter)
############################ example_rmeter GENERATED CODE END ###########################

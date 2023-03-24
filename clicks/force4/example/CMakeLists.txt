cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_force4 LANGUAGES MikroC)
else()
    project(example_force4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_force4
        main.c

)


############################ example_force4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_force4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_force4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_force4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_force4)
target_link_libraries(example_force4 PUBLIC Click.Force4)
############################ example_force4 GENERATED CODE END ###########################

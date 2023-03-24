cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pot4 LANGUAGES MikroC)
else()
    project(example_pot4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pot4
        example/main.c

)


############################ example_pot4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pot4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pot4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pot4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_pot4)
target_link_libraries(example_pot4 PUBLIC Click.POT4)
############################ example_pot4 GENERATED CODE END ###########################

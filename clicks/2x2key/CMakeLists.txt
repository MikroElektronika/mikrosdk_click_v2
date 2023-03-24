cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c2x2key LANGUAGES MikroC)
else()
    project(example_c2x2key LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c2x2key
        example/main.c

)


############################ example_c2x2key GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c2x2key PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c2x2key PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c2x2key PUBLIC MikroSDK.Log)
add_subdirectory(lib_c2x2key)
target_link_libraries(example_c2x2key PUBLIC Click.2x2key)
############################ example_c2x2key GENERATED CODE END ###########################

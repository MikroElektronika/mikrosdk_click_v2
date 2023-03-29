cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_digipot9 LANGUAGES MikroC)
else()
    project(example_digipot9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_digipot9
        example/main.c

)


############################ example_digipot9 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_digipot9 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_digipot9 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_digipot9 PUBLIC MikroSDK.Log)
add_subdirectory(lib_digipot9)
target_link_libraries(example_digipot9 PUBLIC Click.DIGIPOT9)
############################ example_digipot9 GENERATED CODE END ###########################

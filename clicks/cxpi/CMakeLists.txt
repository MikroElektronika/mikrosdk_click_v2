cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_cxpi LANGUAGES MikroC)
else()
    project(example_cxpi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_cxpi
        example/main.c

)


############################ example_cxpi GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_cxpi PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_cxpi PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_cxpi PUBLIC MikroSDK.Log)
add_subdirectory(lib_cxpi)
target_link_libraries(example_cxpi PUBLIC Click.CXPI)
############################ example_cxpi GENERATED CODE END ###########################

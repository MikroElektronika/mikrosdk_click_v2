cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lightranger LANGUAGES MikroC)
else()
    project(example_lightranger LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lightranger
        example/main.c

)


############################ example_lightranger GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lightranger PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lightranger PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lightranger PUBLIC MikroSDK.Log)
add_subdirectory(lib_lightranger)
target_link_libraries(example_lightranger PUBLIC Click.LightRanger)
############################ example_lightranger GENERATED CODE END ###########################

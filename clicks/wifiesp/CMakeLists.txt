cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_wifiesp LANGUAGES MikroC)
else()
    project(example_wifiesp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_wifiesp
        example/main.c

)


############################ example_wifiesp GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_wifiesp PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_wifiesp PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_wifiesp PUBLIC MikroSDK.Log)
add_subdirectory(lib_wifiesp)
target_link_libraries(example_wifiesp PUBLIC Click.WifiEsp)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(example_wifiesp PUBLIC MikroSDK.Conversions)
############################ example_wifiesp GENERATED CODE END ###########################

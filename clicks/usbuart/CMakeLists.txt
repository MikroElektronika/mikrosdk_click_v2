cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_usbuart LANGUAGES MikroC)
else()
    project(example_usbuart LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_usbuart
        example/main.c

)


############################ example_usbuart GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_usbuart PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_usbuart PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_usbuart PUBLIC MikroSDK.Log)
add_subdirectory(lib_usbuart)
target_link_libraries(example_usbuart PUBLIC Click.USBUART)
############################ example_usbuart GENERATED CODE END ###########################

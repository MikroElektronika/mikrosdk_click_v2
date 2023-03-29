cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c5gnbiot LANGUAGES MikroC)
else()
    project(example_c5gnbiot LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c5gnbiot
        main.c

)


############################ example_c5gnbiot GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c5gnbiot PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c5gnbiot PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c5gnbiot PUBLIC MikroSDK.Log)
add_subdirectory(lib_c5gnbiot)
target_link_libraries(example_c5gnbiot PUBLIC Click.5gNbIot)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(example_c5gnbiot PUBLIC MikroSDK.Conversions)
############################ example_c5gnbiot GENERATED CODE END ###########################

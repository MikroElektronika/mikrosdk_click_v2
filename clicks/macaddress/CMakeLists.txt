cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_macaddress LANGUAGES MikroC)
else()
    project(example_macaddress LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_macaddress
        example/main.c

)


############################ example_macaddress GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_macaddress PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_macaddress PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_macaddress PUBLIC MikroSDK.Log)
add_subdirectory(lib_macaddress)
target_link_libraries(example_macaddress PUBLIC Click.MacAddress)
############################ example_macaddress GENERATED CODE END ###########################

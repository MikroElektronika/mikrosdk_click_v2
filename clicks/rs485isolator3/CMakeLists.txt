cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rs485isolator3 LANGUAGES MikroC)
else()
    project(example_rs485isolator3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rs485isolator3
        example/main.c
    
)


############################ example_rs485isolator3 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rs485isolator3 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rs485isolator3 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rs485isolator3 PUBLIC MikroSDK.Log)
add_subdirectory(lib_rs485isolator3)
target_link_libraries(example_rs485isolator3 PUBLIC Click.RS485Isolator3)
############################ example_rs485isolator3 GENERATED CODE END ###########################


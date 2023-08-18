cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rs485isolator LANGUAGES MikroC)
else()
    project(example_rs485isolator LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rs485isolator
        main.c

)


############################ example_rs485isolator GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rs485isolator PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rs485isolator PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rs485isolator PUBLIC MikroSDK.Log)
add_subdirectory(lib_rs485isolator)
target_link_libraries(example_rs485isolator PUBLIC Click.Rs485Isolator)
############################ example_rs485isolator GENERATED CODE END ###########################

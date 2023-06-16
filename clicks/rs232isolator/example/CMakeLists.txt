cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rs232isolator LANGUAGES MikroC)
else()
    project(example_rs232isolator LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rs232isolator
        main.c

)


############################ example_rs232isolator GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rs232isolator PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rs232isolator PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rs232isolator PUBLIC MikroSDK.Log)
add_subdirectory(lib_rs232isolator)
target_link_libraries(example_rs232isolator PUBLIC Click.Rs232Isolator)
############################ example_rs232isolator GENERATED CODE END ###########################

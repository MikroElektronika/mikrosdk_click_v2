cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rs232 LANGUAGES MikroC)
else()
    project(example_rs232 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rs232
        main.c

)


############################ example_rs232 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rs232 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rs232 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rs232 PUBLIC MikroSDK.Log)
add_subdirectory(lib_rs232)
target_link_libraries(example_rs232 PUBLIC Click.Rs232)
############################ example_rs232 GENERATED CODE END ###########################

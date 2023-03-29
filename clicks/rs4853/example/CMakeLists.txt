cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rs4853 LANGUAGES MikroC)
else()
    project(example_rs4853 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rs4853
        main.c

)


############################ example_rs4853 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rs4853 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rs4853 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rs4853 PUBLIC MikroSDK.Log)
add_subdirectory(lib_rs4853)
target_link_libraries(example_rs4853 PUBLIC Click.Rs4853)
############################ example_rs4853 GENERATED CODE END ###########################

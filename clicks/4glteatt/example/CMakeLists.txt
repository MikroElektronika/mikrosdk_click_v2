cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c4glteatt LANGUAGES MikroC)
else()
    project(example_c4glteatt LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c4glteatt
        main.c

)


############################ example_c4glteatt GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c4glteatt PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c4glteatt PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c4glteatt PUBLIC MikroSDK.Log)
add_subdirectory(lib_c4glteatt)
target_link_libraries(example_c4glteatt PUBLIC Click.4GLTEATT)
############################ example_c4glteatt GENERATED CODE END ###########################

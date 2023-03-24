cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c4glte2voice LANGUAGES MikroC)
else()
    project(example_c4glte2voice LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c4glte2voice
        main.c

)


############################ example_c4glte2voice GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c4glte2voice PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c4glte2voice PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c4glte2voice PUBLIC MikroSDK.Log)
add_subdirectory(lib_c4glte2voice)
target_link_libraries(example_c4glte2voice PUBLIC Click.4GLTE2Voice)
############################ example_c4glte2voice GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c4glte2data LANGUAGES MikroC)
else()
    project(example_c4glte2data LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c4glte2data
        example/main.c

)


############################ example_c4glte2data GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c4glte2data PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c4glte2data PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c4glte2data PUBLIC MikroSDK.Log)
add_subdirectory(lib_c4glte2data)
target_link_libraries(example_c4glte2data PUBLIC Click.4GLTE2Data)
############################ example_c4glte2data GENERATED CODE END ###########################

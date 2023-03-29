cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c7x10b LANGUAGES MikroC)
else()
    project(example_c7x10b LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c7x10b
        main.c

)


############################ example_c7x10b GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c7x10b PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c7x10b PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c7x10b PUBLIC MikroSDK.Log)
add_subdirectory(lib_c7x10b)
target_link_libraries(example_c7x10b PUBLIC Click.7x10B)
############################ example_c7x10b GENERATED CODE END ###########################

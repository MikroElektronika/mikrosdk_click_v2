cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_templog LANGUAGES MikroC)
else()
    project(example_templog LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_templog
        main.c

)


############################ example_templog GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_templog PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_templog PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_templog PUBLIC MikroSDK.Log)
add_subdirectory(lib_templog)
target_link_libraries(example_templog PUBLIC Click.TempLog)
############################ example_templog GENERATED CODE END ###########################

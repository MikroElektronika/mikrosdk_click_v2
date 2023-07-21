cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rtd LANGUAGES MikroC)
else()
    project(example_rtd LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rtd
        main.c

)


############################ example_rtd GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rtd PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rtd PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rtd PUBLIC MikroSDK.Log)
add_subdirectory(lib_rtd)
target_link_libraries(example_rtd PUBLIC Click.Rtd)
############################ example_rtd GENERATED CODE END ###########################

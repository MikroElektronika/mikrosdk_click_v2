cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_surfacetemp LANGUAGES MikroC)
else()
    project(example_surfacetemp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_surfacetemp
        main.c

)


############################ example_surfacetemp GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_surfacetemp PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_surfacetemp PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_surfacetemp PUBLIC MikroSDK.Log)
add_subdirectory(lib_surfacetemp)
target_link_libraries(example_surfacetemp PUBLIC Click.SurfaceTemp)
############################ example_surfacetemp GENERATED CODE END ###########################

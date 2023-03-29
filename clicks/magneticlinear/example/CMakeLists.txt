cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_magneticlinear LANGUAGES MikroC)
else()
    project(example_magneticlinear LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_magneticlinear
        main.c

)


############################ example_magneticlinear GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_magneticlinear PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_magneticlinear PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_magneticlinear PUBLIC MikroSDK.Log)
add_subdirectory(lib_magneticlinear)
target_link_libraries(example_magneticlinear PUBLIC Click.Magneticlinear)
############################ example_magneticlinear GENERATED CODE END ###########################

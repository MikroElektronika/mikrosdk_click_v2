cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c7segrgb LANGUAGES MikroC)
else()
    project(example_c7segrgb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c7segrgb
        main.c

)


############################ example_c7segrgb GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c7segrgb PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c7segrgb PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c7segrgb PUBLIC MikroSDK.Log)
add_subdirectory(lib_c7segrgb)
target_link_libraries(example_c7segrgb PUBLIC Click.7SegRgb)
############################ example_c7segrgb GENERATED CODE END ###########################

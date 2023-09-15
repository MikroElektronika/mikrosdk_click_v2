cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_utl7segb LANGUAGES MikroC)
else()
    project(example_utl7segb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_utl7segb
        main.c
    
)


############################ example_utl7segb GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_utl7segb PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_utl7segb PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_utl7segb PUBLIC MikroSDK.Log)
add_subdirectory(lib_utl7segb)
target_link_libraries(example_utl7segb PUBLIC Click.UTL7SEGB)
############################ example_utl7segb GENERATED CODE END ###########################


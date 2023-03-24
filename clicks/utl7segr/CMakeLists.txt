cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_utl7segr LANGUAGES MikroC)
else()
    project(example_utl7segr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_utl7segr
        example/main.c

)


############################ example_utl7segr GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_utl7segr PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_utl7segr PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_utl7segr PUBLIC MikroSDK.Log)
add_subdirectory(lib_utl7segr)
target_link_libraries(example_utl7segr PUBLIC Click.UT-L7-SEGR)
############################ example_utl7segr GENERATED CODE END ###########################

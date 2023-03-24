cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_utm7segr LANGUAGES MikroC)
else()
    project(example_utm7segr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_utm7segr
        main.c

)


############################ example_utm7segr GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_utm7segr PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_utm7segr PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_utm7segr PUBLIC MikroSDK.Log)
add_subdirectory(lib_utm7segr)
target_link_libraries(example_utm7segr PUBLIC Click.UT-M7-SEGR)
############################ example_utm7segr GENERATED CODE END ###########################

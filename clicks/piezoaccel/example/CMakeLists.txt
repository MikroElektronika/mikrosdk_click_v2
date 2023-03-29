cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_piezoaccel LANGUAGES MikroC)
else()
    project(example_piezoaccel LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_piezoaccel
        main.c

)


############################ example_piezoaccel GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_piezoaccel PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_piezoaccel PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_piezoaccel PUBLIC MikroSDK.Log)
add_subdirectory(lib_piezoaccel)
target_link_libraries(example_piezoaccel PUBLIC Click.PiezoAccel)
############################ example_piezoaccel GENERATED CODE END ###########################

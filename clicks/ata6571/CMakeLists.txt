cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ata6571 LANGUAGES MikroC)
else()
    project(example_ata6571 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ata6571
        example/main.c

)


############################ example_ata6571 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ata6571 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ata6571 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ata6571 PUBLIC MikroSDK.Log)
add_subdirectory(lib_ata6571)
target_link_libraries(example_ata6571 PUBLIC Click.ATA6571)
############################ example_ata6571 GENERATED CODE END ###########################

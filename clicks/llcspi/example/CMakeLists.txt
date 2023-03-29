cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_llcspi LANGUAGES MikroC)
else()
    project(example_llcspi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_llcspi
        main.c

)


############################ example_llcspi GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_llcspi PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_llcspi PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_llcspi PUBLIC MikroSDK.Log)
add_subdirectory(lib_llcspi)
target_link_libraries(example_llcspi PUBLIC Click.Llcspi)
############################ example_llcspi GENERATED CODE END ###########################

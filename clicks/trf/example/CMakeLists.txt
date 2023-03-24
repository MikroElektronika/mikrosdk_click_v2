cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_trf LANGUAGES MikroC)
else()
    project(example_trf LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_trf
        main.c

)


############################ example_trf GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_trf PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_trf PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_trf PUBLIC MikroSDK.Log)
add_subdirectory(lib_trf)
target_link_libraries(example_trf PUBLIC Click.Trf)
############################ example_trf GENERATED CODE END ###########################

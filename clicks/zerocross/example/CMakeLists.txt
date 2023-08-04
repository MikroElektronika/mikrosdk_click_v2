cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_zerocross LANGUAGES MikroC)
else()
    project(example_zerocross LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_zerocross
        main.c
    
)


############################ example_zerocross GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_zerocross PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_zerocross PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_zerocross PUBLIC MikroSDK.Log)
add_subdirectory(lib_zerocross)
target_link_libraries(example_zerocross PUBLIC Click.ZeroCross)
############################ example_zerocross GENERATED CODE END ###########################


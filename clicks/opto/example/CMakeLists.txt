cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_opto LANGUAGES MikroC)
else()
    project(example_opto LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_opto
        main.c

)


############################ example_opto GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_opto PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_opto PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_opto PUBLIC MikroSDK.Log)
add_subdirectory(lib_opto)
target_link_libraries(example_opto PUBLIC Click.OPTO)
############################ example_opto GENERATED CODE END ###########################

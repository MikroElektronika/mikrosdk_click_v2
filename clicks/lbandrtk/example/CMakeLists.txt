cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lbandrtk LANGUAGES MikroC)
else()
    project(example_lbandrtk LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lbandrtk
        main.c
    
)


############################ example_lbandrtk GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lbandrtk PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lbandrtk PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lbandrtk PUBLIC MikroSDK.Log)
add_subdirectory(lib_lbandrtk)
target_link_libraries(example_lbandrtk PUBLIC Click.LBANDRTK)
############################ example_lbandrtk GENERATED CODE END ###########################


cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gnssrtk LANGUAGES MikroC)
else()
    project(example_gnssrtk LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gnssrtk
        main.c

)


############################ example_gnssrtk GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gnssrtk PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gnssrtk PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gnssrtk PUBLIC MikroSDK.Log)
add_subdirectory(lib_gnssrtk)
target_link_libraries(example_gnssrtk PUBLIC Click.GNSSRTK)
############################ example_gnssrtk GENERATED CODE END ###########################

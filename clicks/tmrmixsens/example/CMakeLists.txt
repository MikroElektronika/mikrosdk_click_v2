cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_tmrmixsens LANGUAGES MikroC)
else()
    project(example_tmrmixsens LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_tmrmixsens
        main.c

)


############################ example_tmrmixsens GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_tmrmixsens PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_tmrmixsens PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_tmrmixsens PUBLIC MikroSDK.Log)
add_subdirectory(lib_tmrmixsens)
target_link_libraries(example_tmrmixsens PUBLIC Click.Tmrmixsens)
############################ example_tmrmixsens GENERATED CODE END ###########################

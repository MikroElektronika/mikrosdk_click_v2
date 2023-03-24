cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_battmon2 LANGUAGES MikroC)
else()
    project(example_battmon2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_battmon2
        example/main.c

)


############################ example_battmon2 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_battmon2 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_battmon2 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_battmon2 PUBLIC MikroSDK.Log)
add_subdirectory(lib_battmon2)
target_link_libraries(example_battmon2 PUBLIC Click.BATTMON2)
############################ example_battmon2 GENERATED CODE END ###########################

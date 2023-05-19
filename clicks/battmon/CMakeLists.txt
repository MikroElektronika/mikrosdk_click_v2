cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_battmon LANGUAGES MikroC)
else()
    project(example_battmon LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_battmon
        example/main.c

)


############################ example_battmon GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_battmon PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_battmon PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_battmon PUBLIC MikroSDK.Log)
add_subdirectory(lib_battmon)
target_link_libraries(example_battmon PUBLIC Click.BattMon)
############################ example_battmon GENERATED CODE END ###########################

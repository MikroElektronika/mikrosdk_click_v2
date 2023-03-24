cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_boostinv LANGUAGES MikroC)
else()
    project(example_boostinv LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_boostinv
        main.c

)


############################ example_boostinv GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_boostinv PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_boostinv PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_boostinv PUBLIC MikroSDK.Log)
add_subdirectory(lib_boostinv)
target_link_libraries(example_boostinv PUBLIC Click.BoostInv)
############################ example_boostinv GENERATED CODE END ###########################

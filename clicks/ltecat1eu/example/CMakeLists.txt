cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ltecat1eu LANGUAGES MikroC)
else()
    project(example_ltecat1eu LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ltecat1eu
        main.c

)


############################ example_ltecat1eu GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ltecat1eu PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ltecat1eu PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ltecat1eu PUBLIC MikroSDK.Log)
add_subdirectory(lib_ltecat1eu)
target_link_libraries(example_ltecat1eu PUBLIC Click.LTECat1EU)
############################ example_ltecat1eu GENERATED CODE END ###########################

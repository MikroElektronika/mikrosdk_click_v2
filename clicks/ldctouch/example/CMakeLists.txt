cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ldctouch LANGUAGES MikroC)
else()
    project(example_ldctouch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ldctouch
        main.c

)


############################ example_ldctouch GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ldctouch PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ldctouch PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ldctouch PUBLIC MikroSDK.Log)
add_subdirectory(lib_ldctouch)
target_link_libraries(example_ldctouch PUBLIC Click.LDCTouch)
############################ example_ldctouch GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_smoke LANGUAGES MikroC)
else()
    project(example_smoke LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_smoke
        main.c

)


############################ example_smoke GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_smoke PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_smoke PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_smoke PUBLIC MikroSDK.Log)
add_subdirectory(lib_smoke)
target_link_libraries(example_smoke PUBLIC Click.Smoke)
############################ example_smoke GENERATED CODE END ###########################

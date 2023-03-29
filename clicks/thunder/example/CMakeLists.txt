cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_thunder LANGUAGES MikroC)
else()
    project(example_thunder LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_thunder
        main.c

)


############################ example_thunder GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_thunder PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_thunder PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_thunder PUBLIC MikroSDK.Log)
add_subdirectory(lib_thunder)
target_link_libraries(example_thunder PUBLIC Click.Thunder)
############################ example_thunder GENERATED CODE END ###########################

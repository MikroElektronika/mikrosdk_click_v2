cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_bihall LANGUAGES MikroC)
else()
    project(example_bihall LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_bihall
        example/main.c

)


############################ example_bihall GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_bihall PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_bihall PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_bihall PUBLIC MikroSDK.Log)
add_subdirectory(lib_bihall)
target_link_libraries(example_bihall PUBLIC Click.BiHall)
############################ example_bihall GENERATED CODE END ###########################

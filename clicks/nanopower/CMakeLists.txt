cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_nanopower LANGUAGES MikroC)
else()
    project(example_nanopower LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_nanopower
        example/main.c

)


############################ example_nanopower GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_nanopower PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_nanopower PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_nanopower PUBLIC MikroSDK.Log)
add_subdirectory(lib_nanopower)
target_link_libraries(example_nanopower PUBLIC Click.NanoPower)
############################ example_nanopower GENERATED CODE END ###########################

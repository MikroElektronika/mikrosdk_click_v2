cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_reed LANGUAGES MikroC)
else()
    project(example_reed LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_reed
        example/main.c

)


############################ example_reed GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_reed PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_reed PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_reed PUBLIC MikroSDK.Log)
add_subdirectory(lib_reed)
target_link_libraries(example_reed PUBLIC Click.Reed)
############################ example_reed GENERATED CODE END ###########################

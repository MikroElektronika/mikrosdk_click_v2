cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_irdistance LANGUAGES MikroC)
else()
    project(example_irdistance LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_irdistance
        example/main.c

)


############################ example_irdistance GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_irdistance PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_irdistance PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_irdistance PUBLIC MikroSDK.Log)
add_subdirectory(lib_irdistance)
target_link_libraries(example_irdistance PUBLIC Click.IrDistance)
############################ example_irdistance GENERATED CODE END ###########################

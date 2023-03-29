cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_irgrid LANGUAGES MikroC)
else()
    project(example_irgrid LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_irgrid
        example/main.c

)


############################ example_irgrid GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_irgrid PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_irgrid PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_irgrid PUBLIC MikroSDK.Log)
add_subdirectory(lib_irgrid)
target_link_libraries(example_irgrid PUBLIC Click.IRGrid)
############################ example_irgrid GENERATED CODE END ###########################

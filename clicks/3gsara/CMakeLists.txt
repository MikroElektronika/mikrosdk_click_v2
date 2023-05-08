cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c3gsara LANGUAGES MikroC)
else()
    project(example_c3gsara LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c3gsara
        example/main.c

)


############################ example_c3gsara GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c3gsara PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c3gsara PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c3gsara PUBLIC MikroSDK.Log)
add_subdirectory(lib_c3gsara)
target_link_libraries(example_c3gsara PUBLIC Click.3gSara)
############################ example_c3gsara GENERATED CODE END ###########################

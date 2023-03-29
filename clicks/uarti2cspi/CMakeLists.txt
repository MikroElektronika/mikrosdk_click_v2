cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_uarti2cspi LANGUAGES MikroC)
else()
    project(example_uarti2cspi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_uarti2cspi
        example/main.c

)


############################ example_uarti2cspi GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_uarti2cspi PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_uarti2cspi PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_uarti2cspi PUBLIC MikroSDK.Log)
add_subdirectory(lib_uarti2cspi)
target_link_libraries(example_uarti2cspi PUBLIC Click.UARTI2CSPI)
############################ example_uarti2cspi GENERATED CODE END ###########################

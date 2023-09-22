cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_usbuartiso LANGUAGES MikroC)
else()
    project(example_usbuartiso LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_usbuartiso
        main.c
    
)


############################ example_usbuartiso GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_usbuartiso PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_usbuartiso PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_usbuartiso PUBLIC MikroSDK.Log)
add_subdirectory(lib_usbuartiso)
target_link_libraries(example_usbuartiso PUBLIC Click.USBUARTISO)
############################ example_usbuartiso GENERATED CODE END ###########################


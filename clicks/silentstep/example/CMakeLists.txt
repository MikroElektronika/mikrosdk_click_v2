cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_silentstep LANGUAGES MikroC)
else()
    project(example_silentstep LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_silentstep
        main.c
    
)


############################ example_silentstep GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_silentstep PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_silentstep PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_silentstep PUBLIC MikroSDK.Log)
add_subdirectory(lib_silentstep)
target_link_libraries(example_silentstep PUBLIC Click.SilentStep)
############################ example_silentstep GENERATED CODE END ###########################


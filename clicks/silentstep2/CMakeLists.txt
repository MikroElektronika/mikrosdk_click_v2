cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_silentstep2 LANGUAGES MikroC)
else()
    project(example_silentstep2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_silentstep2
        example/main.c
    
)


############################ example_silentstep2 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_silentstep2 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_silentstep2 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_silentstep2 PUBLIC MikroSDK.Log)
add_subdirectory(lib_silentstep2)
target_link_libraries(example_silentstep2 PUBLIC Click.SilentStep2)
############################ example_silentstep2 GENERATED CODE END ###########################


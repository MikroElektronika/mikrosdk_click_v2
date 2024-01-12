cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ezocarrierph LANGUAGES MikroC)
else()
    project(example_ezocarrierph LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ezocarrierph
        example/main.c
    
)


############################ example_ezocarrierph GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ezocarrierph PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ezocarrierph PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ezocarrierph PUBLIC MikroSDK.Log)
add_subdirectory(lib_ezocarrierph)
target_link_libraries(example_ezocarrierph PUBLIC Click.EZOCarrierpH)
############################ example_ezocarrierph GENERATED CODE END ###########################


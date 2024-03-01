cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ezocarrierorp LANGUAGES MikroC)
else()
    project(example_ezocarrierorp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ezocarrierorp
        example/main.c
    
)


############################ example_ezocarrierorp GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ezocarrierorp PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ezocarrierorp PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ezocarrierorp PUBLIC MikroSDK.Log)
add_subdirectory(lib_ezocarrierorp)
target_link_libraries(example_ezocarrierorp PUBLIC Click.EZOCarrierORP)
############################ example_ezocarrierorp GENERATED CODE END ###########################


cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ezocarrierec LANGUAGES MikroC)
else()
    project(example_ezocarrierec LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ezocarrierec
        example/main.c
    
)


############################ example_ezocarrierec GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ezocarrierec PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ezocarrierec PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ezocarrierec PUBLIC MikroSDK.Log)
add_subdirectory(lib_ezocarrierec)
target_link_libraries(example_ezocarrierec PUBLIC Click.EZOCarrierEC)
############################ example_ezocarrierec GENERATED CODE END ###########################


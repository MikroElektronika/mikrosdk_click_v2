cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ezocarrierrtd LANGUAGES MikroC)
else()
    project(example_ezocarrierrtd LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ezocarrierrtd
        example/main.c
    
)


############################ example_ezocarrierrtd GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ezocarrierrtd PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ezocarrierrtd PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ezocarrierrtd PUBLIC MikroSDK.Log)
add_subdirectory(lib_ezocarrierrtd)
target_link_libraries(example_ezocarrierrtd PUBLIC Click.EZOCarrierRTD)
############################ example_ezocarrierrtd GENERATED CODE END ###########################


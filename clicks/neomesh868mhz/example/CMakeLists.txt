cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_neomesh868mhz LANGUAGES MikroC)
else()
    project(example_neomesh868mhz LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_neomesh868mhz
        main.c
    
)


############################ example_neomesh868mhz GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_neomesh868mhz PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_neomesh868mhz PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_neomesh868mhz PUBLIC MikroSDK.Log)
add_subdirectory(lib_neomesh868mhz)
target_link_libraries(example_neomesh868mhz PUBLIC Click.NeoMesh868MHz)
############################ example_neomesh868mhz GENERATED CODE END ###########################


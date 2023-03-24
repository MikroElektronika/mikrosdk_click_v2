cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c1wireswitch LANGUAGES MikroC)
else()
    project(example_c1wireswitch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c1wireswitch
        main.c
    
)


############################ example_c1wireswitch GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c1wireswitch PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c1wireswitch PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c1wireswitch PUBLIC MikroSDK.Log)
add_subdirectory(lib_c1wireswitch)
target_link_libraries(example_c1wireswitch PUBLIC Click.c1WireSwitch)
############################ example_c1wireswitch GENERATED CODE END ###########################


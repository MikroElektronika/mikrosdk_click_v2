cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_solidswitch LANGUAGES MikroC)
else()
    project(example_solidswitch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_solidswitch
        main.c

)


############################ example_solidswitch GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_solidswitch PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_solidswitch PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_solidswitch PUBLIC MikroSDK.Log)
add_subdirectory(lib_solidswitch)
target_link_libraries(example_solidswitch PUBLIC Click.SolidSwitch)
############################ example_solidswitch GENERATED CODE END ###########################

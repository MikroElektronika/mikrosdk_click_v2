cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_proximity6 LANGUAGES MikroC)
else()
    project(example_proximity6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_proximity6
        main.c

)


############################ example_proximity6 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_proximity6 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_proximity6 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_proximity6 PUBLIC MikroSDK.Log)
add_subdirectory(lib_proximity6)
target_link_libraries(example_proximity6 PUBLIC Click.Proximity6)
############################ example_proximity6 GENERATED CODE END ###########################

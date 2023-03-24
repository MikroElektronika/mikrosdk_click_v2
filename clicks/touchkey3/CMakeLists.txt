cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_touchkey3 LANGUAGES MikroC)
else()
    project(example_touchkey3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_touchkey3
        example/main.c

)


############################ example_touchkey3 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_touchkey3 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_touchkey3 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_touchkey3 PUBLIC MikroSDK.Log)
add_subdirectory(lib_touchkey3)
target_link_libraries(example_touchkey3 PUBLIC Click.TouchKey3)
############################ example_touchkey3 GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_temphum19 LANGUAGES MikroC)
else()
    project(example_temphum19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_temphum19
        example/main.c

)


############################ example_temphum19 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_temphum19 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_temphum19 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_temphum19 PUBLIC MikroSDK.Log)
add_subdirectory(lib_temphum19)
target_link_libraries(example_temphum19 PUBLIC Click.TempHum19)
############################ example_temphum19 GENERATED CODE END ###########################

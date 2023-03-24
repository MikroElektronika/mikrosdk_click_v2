cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_temphum23 LANGUAGES MikroC)
else()
    project(example_temphum23 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_temphum23
        example/main.c

)


############################ example_temphum23 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_temphum23 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_temphum23 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_temphum23 PUBLIC MikroSDK.Log)
add_subdirectory(lib_temphum23)
target_link_libraries(example_temphum23 PUBLIC Click.TempHum23)
############################ example_temphum23 GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rs2322 LANGUAGES MikroC)
else()
    project(example_rs2322 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rs2322
        main.c

)


############################ example_rs2322 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rs2322 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rs2322 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rs2322 PUBLIC MikroSDK.Log)
add_subdirectory(lib_rs2322)
target_link_libraries(example_rs2322 PUBLIC Click.Rs2322)
############################ example_rs2322 GENERATED CODE END ###########################

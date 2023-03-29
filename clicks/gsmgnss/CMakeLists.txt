cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gsmgnss LANGUAGES MikroC)
else()
    project(example_gsmgnss LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gsmgnss
        example/main.c

)


############################ example_gsmgnss GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gsmgnss PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gsmgnss PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gsmgnss PUBLIC MikroSDK.Log)
add_subdirectory(lib_gsmgnss)
target_link_libraries(example_gsmgnss PUBLIC Click.GsmGnss)
############################ example_gsmgnss GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_powermux LANGUAGES MikroC)
else()
    project(example_powermux LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_powermux
        example/main.c

)


############################ example_powermux GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_powermux PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_powermux PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_powermux PUBLIC MikroSDK.Log)
add_subdirectory(lib_powermux)
target_link_libraries(example_powermux PUBLIC Click.PowerMUX)
############################ example_powermux GENERATED CODE END ###########################

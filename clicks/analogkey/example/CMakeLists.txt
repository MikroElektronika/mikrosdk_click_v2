cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_analogkey LANGUAGES MikroC)
else()
    project(example_analogkey LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_analogkey
        main.c

)


############################ example_analogkey GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_analogkey PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_analogkey PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_analogkey PUBLIC MikroSDK.Log)
add_subdirectory(lib_analogkey)
target_link_libraries(example_analogkey PUBLIC Click.AnalogKey)
############################ example_analogkey GENERATED CODE END ###########################

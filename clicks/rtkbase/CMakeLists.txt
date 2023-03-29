cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rtkbase LANGUAGES MikroC)
else()
    project(example_rtkbase LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rtkbase
        example/main.c

)


############################ example_rtkbase GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rtkbase PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rtkbase PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rtkbase PUBLIC MikroSDK.Log)
add_subdirectory(lib_rtkbase)
target_link_libraries(example_rtkbase PUBLIC Click.RTKBase)
############################ example_rtkbase GENERATED CODE END ###########################

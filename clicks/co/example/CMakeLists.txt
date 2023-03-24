cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_co LANGUAGES MikroC)
else()
    project(example_co LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_co
        main.c

)


############################ example_co GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_co PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_co PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_co PUBLIC MikroSDK.Log)
add_subdirectory(lib_co)
target_link_libraries(example_co PUBLIC Click.CO)
############################ example_co GENERATED CODE END ###########################

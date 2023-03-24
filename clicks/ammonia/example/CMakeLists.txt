cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ammonia LANGUAGES MikroC)
else()
    project(example_ammonia LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ammonia
        main.c

)


############################ example_ammonia GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ammonia PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ammonia PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ammonia PUBLIC MikroSDK.Log)
add_subdirectory(lib_ammonia)
target_link_libraries(example_ammonia PUBLIC Click.Ammonia)
############################ example_ammonia GENERATED CODE END ###########################

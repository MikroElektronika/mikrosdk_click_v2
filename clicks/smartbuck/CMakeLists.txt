cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_smartbuck LANGUAGES MikroC)
else()
    project(example_smartbuck LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_smartbuck
        example/main.c

)


############################ example_smartbuck GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_smartbuck PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_smartbuck PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_smartbuck PUBLIC MikroSDK.Log)
add_subdirectory(lib_smartbuck)
target_link_libraries(example_smartbuck PUBLIC Click.SMARTBUCK)
############################ example_smartbuck GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_wheatstone LANGUAGES MikroC)
else()
    project(example_wheatstone LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_wheatstone
        example/main.c

)


############################ example_wheatstone GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_wheatstone PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_wheatstone PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_wheatstone PUBLIC MikroSDK.Log)
add_subdirectory(lib_wheatstone)
target_link_libraries(example_wheatstone PUBLIC Click.Wheatstone)
############################ example_wheatstone GENERATED CODE END ###########################

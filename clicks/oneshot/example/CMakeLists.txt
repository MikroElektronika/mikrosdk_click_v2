cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_oneshot LANGUAGES MikroC)
else()
    project(example_oneshot LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_oneshot
        main.c

)


############################ example_oneshot GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_oneshot PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_oneshot PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_oneshot PUBLIC MikroSDK.Log)
add_subdirectory(lib_oneshot)
target_link_libraries(example_oneshot PUBLIC Click.OneShot)
############################ example_oneshot GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_manometer LANGUAGES MikroC)
else()
    project(example_manometer LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_manometer
        example/main.c

)


############################ example_manometer GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_manometer PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_manometer PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_manometer PUBLIC MikroSDK.Log)
add_subdirectory(lib_manometer)
target_link_libraries(example_manometer PUBLIC Click.Manometer)
############################ example_manometer GENERATED CODE END ###########################

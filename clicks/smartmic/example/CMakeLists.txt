cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_smartmic LANGUAGES MikroC)
else()
    project(example_smartmic LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_smartmic
        main.c

)


############################ example_smartmic GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_smartmic PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_smartmic PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_smartmic PUBLIC MikroSDK.Log)
add_subdirectory(lib_smartmic)
target_link_libraries(example_smartmic PUBLIC Click.SmartMic)
############################ example_smartmic GENERATED CODE END ###########################

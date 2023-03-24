cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_buttonpower LANGUAGES MikroC)
else()
    project(example_buttonpower LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_buttonpower
        main.c

)


############################ example_buttonpower GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_buttonpower PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_buttonpower PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_buttonpower PUBLIC MikroSDK.Log)
add_subdirectory(lib_buttonpower)
target_link_libraries(example_buttonpower PUBLIC Click.ButtonPower)
############################ example_buttonpower GENERATED CODE END ###########################

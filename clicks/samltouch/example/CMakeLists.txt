cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_samltouch LANGUAGES MikroC)
else()
    project(example_samltouch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_samltouch
        main.c

)


############################ example_samltouch GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_samltouch PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_samltouch PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_samltouch PUBLIC MikroSDK.Log)
add_subdirectory(lib_samltouch)
target_link_libraries(example_samltouch PUBLIC Click.SamlTouch)
############################ example_samltouch GENERATED CODE END ###########################

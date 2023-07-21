cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_adswio2 LANGUAGES MikroC)
else()
    project(example_adswio2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_adswio2
        example/main.c

)


############################ example_adswio2 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_adswio2 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_adswio2 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_adswio2 PUBLIC MikroSDK.Log)
add_subdirectory(lib_adswio2)
target_link_libraries(example_adswio2 PUBLIC Click.AdSwio2)
############################ example_adswio2 GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pac1921 LANGUAGES MikroC)
else()
    project(example_pac1921 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pac1921
        example/main.c

)


############################ example_pac1921 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pac1921 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pac1921 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pac1921 PUBLIC MikroSDK.Log)
add_subdirectory(lib_pac1921)
target_link_libraries(example_pac1921 PUBLIC Click.PAC1921)
############################ example_pac1921 GENERATED CODE END ###########################

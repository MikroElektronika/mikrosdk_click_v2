cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_buttong LANGUAGES MikroC)
else()
    project(example_buttong LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_buttong
        example/main.c

)


############################ example_buttong GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_buttong PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_buttong PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_buttong PUBLIC MikroSDK.Log)
add_subdirectory(lib_buttong)
target_link_libraries(example_buttong PUBLIC Click.ButtonG)
############################ example_buttong GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_optoencoder LANGUAGES MikroC)
else()
    project(example_optoencoder LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_optoencoder
        example/main.c

)


############################ example_optoencoder GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_optoencoder PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_optoencoder PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_optoencoder PUBLIC MikroSDK.Log)
add_subdirectory(lib_optoencoder)
target_link_libraries(example_optoencoder PUBLIC Click.OptoEncoder)
############################ example_optoencoder GENERATED CODE END ###########################

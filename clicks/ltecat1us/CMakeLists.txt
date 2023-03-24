cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ltecat1us LANGUAGES MikroC)
else()
    project(example_ltecat1us LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ltecat1us
        example/main.c

)


############################ example_ltecat1us GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ltecat1us PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ltecat1us PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ltecat1us PUBLIC MikroSDK.Log)
add_subdirectory(lib_ltecat1us)
target_link_libraries(example_ltecat1us PUBLIC Click.LTECat1US)
############################ example_ltecat1us GENERATED CODE END ###########################

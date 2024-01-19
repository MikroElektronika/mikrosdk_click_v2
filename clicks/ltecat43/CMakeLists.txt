cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ltecat43 LANGUAGES MikroC)
else()
    project(example_ltecat43 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ltecat43
        example/main.c

)


############################ example_ltecat43 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ltecat43 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ltecat43 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ltecat43 PUBLIC MikroSDK.Log)
add_subdirectory(lib_ltecat43)
target_link_libraries(example_ltecat43 PUBLIC Click.LTECat43)
############################ example_ltecat43 GENERATED CODE END ###########################

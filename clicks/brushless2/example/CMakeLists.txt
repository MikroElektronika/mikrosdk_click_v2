cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_brushless2 LANGUAGES MikroC)
else()
    project(example_brushless2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_brushless2
        main.c

)


############################ example_brushless2 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_brushless2 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_brushless2 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_brushless2 PUBLIC MikroSDK.Log)
add_subdirectory(lib_brushless2)
target_link_libraries(example_brushless2 PUBLIC Click.Brushless2)
############################ example_brushless2 GENERATED CODE END ###########################

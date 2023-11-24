cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ooktx LANGUAGES MikroC)
else()
    project(example_ooktx LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ooktx
        main.c
    
)


############################ example_ooktx GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ooktx PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ooktx PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ooktx PUBLIC MikroSDK.Log)
add_subdirectory(lib_ooktx)
target_link_libraries(example_ooktx PUBLIC Click.OOKTX)
############################ example_ooktx GENERATED CODE END ###########################


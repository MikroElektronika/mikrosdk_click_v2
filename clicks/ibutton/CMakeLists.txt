cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ibutton LANGUAGES MikroC)
else()
    project(example_ibutton LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ibutton
        example/main.c
    
)


############################ example_ibutton GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ibutton PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ibutton PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ibutton PUBLIC MikroSDK.Log)
add_subdirectory(lib_ibutton)
target_link_libraries(example_ibutton PUBLIC Click.iButton)
############################ example_ibutton GENERATED CODE END ###########################


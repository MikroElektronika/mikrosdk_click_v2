cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_dtmf LANGUAGES MikroC)
else()
    project(example_dtmf LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_dtmf
        example/main.c
    
)


############################ example_dtmf GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_dtmf PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_dtmf PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_dtmf PUBLIC MikroSDK.Log)
add_subdirectory(lib_dtmf)
target_link_libraries(example_dtmf PUBLIC Click.DTMF)
############################ example_dtmf GENERATED CODE END ###########################


cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_tempalarm LANGUAGES MikroC)
else()
    project(example_tempalarm LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_tempalarm
        example/main.c
    
)


############################ example_tempalarm GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_tempalarm PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_tempalarm PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_tempalarm PUBLIC MikroSDK.Log)
add_subdirectory(lib_tempalarm)
target_link_libraries(example_tempalarm PUBLIC Click.TempAlarm)
############################ example_tempalarm GENERATED CODE END ###########################


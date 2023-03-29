cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_buttonalarm LANGUAGES MikroC)
else()
    project(example_buttonalarm LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_buttonalarm
        example/main.c

)


############################ example_buttonalarm GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_buttonalarm PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_buttonalarm PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_buttonalarm PUBLIC MikroSDK.Log)
add_subdirectory(lib_buttonalarm)
target_link_libraries(example_buttonalarm PUBLIC Click.ButtonAlarm)
############################ example_buttonalarm GENERATED CODE END ###########################

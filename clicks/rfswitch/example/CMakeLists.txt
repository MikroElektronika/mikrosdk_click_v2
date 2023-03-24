cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rfswitch LANGUAGES MikroC)
else()
    project(example_rfswitch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rfswitch
        main.c

)


############################ example_rfswitch GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rfswitch PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rfswitch PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rfswitch PUBLIC MikroSDK.Log)
add_subdirectory(lib_rfswitch)
target_link_libraries(example_rfswitch PUBLIC Click.RFSwitch)
############################ example_rfswitch GENERATED CODE END ###########################

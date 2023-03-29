cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_thermo25 LANGUAGES MikroC)
else()
    project(example_thermo25 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_thermo25
        main.c

)


############################ example_thermo25 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_thermo25 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_thermo25 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_thermo25 PUBLIC MikroSDK.Log)
add_subdirectory(lib_thermo25)
target_link_libraries(example_thermo25 PUBLIC Click.Thermo25)
############################ example_thermo25 GENERATED CODE END ###########################

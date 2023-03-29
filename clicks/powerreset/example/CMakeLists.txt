cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_powerreset LANGUAGES MikroC)
else()
    project(example_powerreset LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_powerreset
        main.c

)


############################ example_powerreset GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_powerreset PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_powerreset PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_powerreset PUBLIC MikroSDK.Log)
add_subdirectory(lib_powerreset)
target_link_libraries(example_powerreset PUBLIC Click.PowerReset)
############################ example_powerreset GENERATED CODE END ###########################

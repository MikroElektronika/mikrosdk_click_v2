cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_solenoiddriver LANGUAGES MikroC)
else()
    project(example_solenoiddriver LANGUAGES C ASM)
endif()

include(mikroeUtils)

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_solenoiddriver
        example/main.c
    
)


############################ example_solenoiddriver GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_solenoiddriver PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_solenoiddriver PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_solenoiddriver PUBLIC MikroSDK.Log)
add_subdirectory(lib_solenoiddriver)
target_link_libraries(example_solenoiddriver PUBLIC Click.SolenoidDriver)
############################ example_solenoiddriver GENERATED CODE END ###########################

if(COMPILER_REVISION)
    if(${COMPILER_REVISION} VERSION_GREATER_EQUAL "1.0")
        if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.meproject)
                fetch_startup_name(${CMAKE_CURRENT_SOURCE_DIR}/.meproject startupName)
                if(startupName)
                    add_startup_all_targets(. ${CMAKE_CURRENT_SOURCE_DIR} ${startupName})
                endif()
                fetch_linker_name(${CMAKE_CURRENT_SOURCE_DIR}/.meproject linkerName)
                if(linkerName)
                    add_ld_all_targets(. ${CMAKE_CURRENT_SOURCE_DIR} ${linkerName})
                endif()
            endif()
        endif()
    endif()
endif()

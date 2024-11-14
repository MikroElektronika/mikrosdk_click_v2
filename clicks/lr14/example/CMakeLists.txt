cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lr14 LANGUAGES MikroC)
else()
    project(example_lr14 LANGUAGES C ASM)
endif()

include(mikroeUtils)

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lr14
        main.c
    
)


############################ example_lr14 GENERATED CODE START ###########################
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lr14 PUBLIC MikroSDK.Log)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(example_lr14 PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(example_lr14 PUBLIC MikroSDK.GenericPointer)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lr14 PUBLIC MikroSDK.Board)
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lr14 PUBLIC MikroC.Core)
add_subdirectory(lib_lr14)
target_link_libraries(example_lr14 PUBLIC Click.LR14)
############################ example_lr14 GENERATED CODE END ###########################

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



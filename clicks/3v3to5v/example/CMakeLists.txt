cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c3v3to5v LANGUAGES MikroC)
else()
    project(example_c3v3to5v LANGUAGES C ASM)
endif()

include(mikroeUtils)

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c3v3to5v
        main.c
    
)


############################ example_c3v3to5v GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c3v3to5v PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c3v3to5v PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c3v3to5v PUBLIC MikroSDK.Log)
add_subdirectory(lib_c3v3to5v)
target_link_libraries(example_c3v3to5v PUBLIC Click.3V3to5V)
############################ example_c3v3to5v GENERATED CODE END ###########################

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

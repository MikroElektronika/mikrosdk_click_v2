cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_powerstep LANGUAGES MikroC)
else()
    project(example_powerstep LANGUAGES C ASM)
endif()

include(mikroeUtils)

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_powerstep
        main.c
    
)


############################ example_powerstep GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_powerstep PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_powerstep PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_powerstep PUBLIC MikroSDK.Log)
add_subdirectory(lib_powerstep)
target_link_libraries(example_powerstep PUBLIC Click.PowerStep)
############################ example_powerstep GENERATED CODE END ###########################

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

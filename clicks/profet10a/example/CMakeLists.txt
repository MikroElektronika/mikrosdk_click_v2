cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_profet10a LANGUAGES MikroC)
else()
    project(example_profet10a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_profet10a
        main.c

)


############################ example_profet10a GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_profet10a PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_profet10a PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_profet10a PUBLIC MikroSDK.Log)
add_subdirectory(lib_profet10a)
target_link_libraries(example_profet10a PUBLIC Click.PROFET10A)
############################ example_profet10a GENERATED CODE END ###########################

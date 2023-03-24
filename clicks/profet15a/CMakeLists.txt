cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_profet15a LANGUAGES MikroC)
else()
    project(example_profet15a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_profet15a
        example/main.c

)


############################ example_profet15a GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_profet15a PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_profet15a PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_profet15a PUBLIC MikroSDK.Log)
add_subdirectory(lib_profet15a)
target_link_libraries(example_profet15a PUBLIC Click.PROFET15A)
############################ example_profet15a GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_vtohz LANGUAGES MikroC)
else()
    project(example_vtohz LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_vtohz
        main.c

)


############################ example_vtohz GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_vtohz PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_vtohz PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_vtohz PUBLIC MikroSDK.Log)
add_subdirectory(lib_vtohz)
target_link_libraries(example_vtohz PUBLIC Click.VtoHz)
############################ example_vtohz GENERATED CODE END ###########################

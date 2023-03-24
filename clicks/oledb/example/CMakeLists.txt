cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_oledb LANGUAGES MikroC)
else()
    project(example_oledb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_oledb
        main.c

)


############################ example_oledb GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_oledb PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_oledb PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_oledb PUBLIC MikroSDK.Log)
add_subdirectory(lib_oledb)
target_link_libraries(example_oledb PUBLIC Click.OLEDB)
############################ example_oledb GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lps22hb LANGUAGES MikroC)
else()
    project(example_lps22hb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lps22hb
        example/main.c

)


############################ example_lps22hb GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lps22hb PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lps22hb PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lps22hb PUBLIC MikroSDK.Log)
add_subdirectory(lib_lps22hb)
target_link_libraries(example_lps22hb PUBLIC Click.Lps22hb)
############################ example_lps22hb GENERATED CODE END ###########################

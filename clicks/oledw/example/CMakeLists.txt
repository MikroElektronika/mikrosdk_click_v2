cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_oledw LANGUAGES MikroC)
else()
    project(example_oledw LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_oledw
        main.c

)


############################ example_oledw GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_oledw PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_oledw PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_oledw PUBLIC MikroSDK.Log)
add_subdirectory(lib_oledw)
target_link_libraries(example_oledw PUBLIC Click.OLEDW)
############################ example_oledw GENERATED CODE END ###########################

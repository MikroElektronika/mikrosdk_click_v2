cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_eink LANGUAGES MikroC)
else()
    project(example_eink LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_eink
        example/main.c

)

if ((${MCU_NAME} MATCHES "(^PIC18F)") OR (${MCU_NAME} MATCHES "(^dsPIC)") OR (${MCU_NAME} MATCHES "(^ATMEGA)"))
	add_compile_definitions(IMAGE_MODE_ONLY)
endif()

############################ example_eink GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_eink PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_eink PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_eink PUBLIC MikroSDK.Log)
add_subdirectory(lib_eink)
target_link_libraries(example_eink PUBLIC Click.Eink)
############################ example_eink GENERATED CODE END ###########################

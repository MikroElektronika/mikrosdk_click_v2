cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_eink154inch LANGUAGES MikroC)
else()
    project(example_eink154inch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_eink154inch
        example/main.c

)

if (${MCU_NAME} MATCHES "(^PIC18F)|(^ATMEGA)")
	add_compile_definitions(IMAGE_MODE_ONLY)
endif()

############################ example_eink154inch GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_eink154inch PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_eink154inch PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_eink154inch PUBLIC MikroSDK.Log)
add_subdirectory(lib_eink154inch)
target_link_libraries(example_eink154inch PUBLIC Click.Eink154Inch)
############################ example_eink154inch GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rfid LANGUAGES MikroC)
else()
    project(example_rfid LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rfid
        main.c

)


############################ example_rfid GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rfid PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rfid PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rfid PUBLIC MikroSDK.Log)
add_subdirectory(lib_rfid)
target_link_libraries(example_rfid PUBLIC Click.RFID)
############################ example_rfid GENERATED CODE END ###########################

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_nfc4 LANGUAGES MikroC)
else()
    project(example_nfc4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_nfc4
        main.c

)


############################ example_nfc4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_nfc4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_nfc4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_nfc4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_nfc4)
target_link_libraries(example_nfc4 PUBLIC Click.NFC4)
############################ example_nfc4 GENERATED CODE END ###########################

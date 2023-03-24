cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_spectrometer LANGUAGES MikroC)
else()
    project(example_spectrometer LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_spectrometer
        main.c

)


############################ example_spectrometer GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_spectrometer PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_spectrometer PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_spectrometer PUBLIC MikroSDK.Log)
add_subdirectory(lib_spectrometer)
target_link_libraries(example_spectrometer PUBLIC Click.Spectrometer)
############################ example_spectrometer GENERATED CODE END ###########################

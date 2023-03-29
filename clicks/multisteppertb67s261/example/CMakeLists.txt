cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_multisteppertb67s261 LANGUAGES MikroC)
else()
    project(example_multisteppertb67s261 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_multisteppertb67s261
        main.c

)


############################ example_multisteppertb67s261 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_multisteppertb67s261 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_multisteppertb67s261 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_multisteppertb67s261 PUBLIC MikroSDK.Log)
add_subdirectory(lib_multisteppertb67s261)
target_link_libraries(example_multisteppertb67s261 PUBLIC Click.MultiStepperTB67S261)
############################ example_multisteppertb67s261 GENERATED CODE END ###########################

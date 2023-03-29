cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ireclipse LANGUAGES MikroC)
else()
    project(example_ireclipse LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ireclipse
        main.c

)


############################ example_ireclipse GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ireclipse PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ireclipse PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ireclipse PUBLIC MikroSDK.Log)
add_subdirectory(lib_ireclipse)
target_link_libraries(example_ireclipse PUBLIC Click.IrEclipse)
############################ example_ireclipse GENERATED CODE END ###########################

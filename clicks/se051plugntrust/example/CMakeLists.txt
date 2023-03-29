cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_se051plugntrust LANGUAGES MikroC)
else()
    project(example_se051plugntrust LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_se051plugntrust
        main.c

)


############################ example_se051plugntrust GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_se051plugntrust PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_se051plugntrust PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_se051plugntrust PUBLIC MikroSDK.Log)
add_subdirectory(lib_se051plugntrust)
target_link_libraries(example_se051plugntrust PUBLIC Click.SE051PlugnTrust)
############################ example_se051plugntrust GENERATED CODE END ###########################

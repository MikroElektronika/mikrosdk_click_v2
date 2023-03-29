cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_canfd LANGUAGES MikroC)
else()
    project(example_canfd LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_canfd
        example/main.c

)


############################ example_canfd GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_canfd PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_canfd PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_canfd PUBLIC MikroSDK.Log)
add_subdirectory(lib_canfd)
target_link_libraries(example_canfd PUBLIC Click.CanFd)
############################ example_canfd GENERATED CODE END ###########################

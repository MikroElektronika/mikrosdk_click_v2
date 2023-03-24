cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_canfd LANGUAGES MikroC)
else()
    project(lib_canfd LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_canfd STATIC
        src/canfd.c
        include/canfd.h
)
add_library(Click.CanFd  ALIAS lib_canfd)



target_include_directories(lib_canfd PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_canfd PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_canfd PUBLIC MikroSDK.Driver)

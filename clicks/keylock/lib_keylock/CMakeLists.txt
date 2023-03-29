cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_keylock LANGUAGES MikroC)
else()
    project(lib_keylock LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_keylock STATIC
        src/keylock.c
        include/keylock.h
)
add_library(Click.Keylock  ALIAS lib_keylock)



target_include_directories(lib_keylock PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_keylock PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_keylock PUBLIC MikroSDK.Driver)

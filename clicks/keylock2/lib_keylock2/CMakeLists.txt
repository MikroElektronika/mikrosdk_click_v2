cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_keylock2 LANGUAGES MikroC)
else()
    project(lib_keylock2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_keylock2 STATIC
        src/keylock2.c
        include/keylock2.h
)
add_library(Click.KeyLock2  ALIAS lib_keylock2)



target_include_directories(lib_keylock2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_keylock2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_keylock2 PUBLIC MikroSDK.Driver)

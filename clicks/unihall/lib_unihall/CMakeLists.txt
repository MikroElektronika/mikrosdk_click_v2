cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_unihall LANGUAGES MikroC)
else()
    project(lib_unihall LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_unihall STATIC
        src/unihall.c
        include/unihall.h
)
add_library(Click.UniHall  ALIAS lib_unihall)



target_include_directories(lib_unihall PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_unihall PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_unihall PUBLIC MikroSDK.Driver)

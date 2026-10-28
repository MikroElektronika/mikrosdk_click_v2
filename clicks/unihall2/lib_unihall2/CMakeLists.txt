cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_unihall2 LANGUAGES MikroC)
else()
    project(lib_unihall2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_unihall2 STATIC
        src/unihall2.c
        include/unihall2.h
)
add_library(Click.UNIHall2  ALIAS lib_unihall2)



target_include_directories(lib_unihall2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_unihall2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_unihall2 PUBLIC MikroSDK.Driver)


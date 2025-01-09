cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proteuse LANGUAGES MikroC)
else()
    project(lib_proteuse LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proteuse STATIC
        src/proteuse.c
        include/proteuse.h
)
add_library(Click.Proteuse  ALIAS lib_proteuse)



target_include_directories(lib_proteuse PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proteuse PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proteuse PUBLIC MikroSDK.Driver)


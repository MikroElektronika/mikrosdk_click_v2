cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ookrx LANGUAGES MikroC)
else()
    project(lib_ookrx LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ookrx STATIC
        src/ookrx.c
        include/ookrx.h
)
add_library(Click.OOKRX  ALIAS lib_ookrx)



target_include_directories(lib_ookrx PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ookrx PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ookrx PUBLIC MikroSDK.Driver)


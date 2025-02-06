cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tester2 LANGUAGES MikroC)
else()
    project(lib_tester2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tester2 STATIC
        src/tester2.c
        include/tester2.h
)
add_library(Click.Tester2  ALIAS lib_tester2)



target_include_directories(lib_tester2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tester2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tester2 PUBLIC MikroSDK.Driver)


cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tester3 LANGUAGES MikroC)
else()
    project(lib_tester3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tester3 STATIC
        src/tester3.c
        include/tester3.h
)
add_library(Click.Tester3  ALIAS lib_tester3)



target_include_directories(lib_tester3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tester3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tester3 PUBLIC MikroSDK.Driver)


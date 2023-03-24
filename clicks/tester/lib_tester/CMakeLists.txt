cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tester LANGUAGES MikroC)
else()
    project(lib_tester LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tester STATIC
        src/tester.c
        include/tester.h
)
add_library(Click.Tester  ALIAS lib_tester)



target_include_directories(lib_tester PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tester PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tester PUBLIC MikroSDK.Driver)

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_profet15a LANGUAGES MikroC)
else()
    project(lib_profet15a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_profet15a STATIC
        src/profet15a.c
        include/profet15a.h
)
add_library(Click.PROFET15A  ALIAS lib_profet15a)



target_include_directories(lib_profet15a PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_profet15a PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_profet15a PUBLIC MikroSDK.Driver)

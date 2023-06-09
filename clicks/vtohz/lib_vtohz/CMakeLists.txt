cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_vtohz LANGUAGES MikroC)
else()
    project(lib_vtohz LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_vtohz STATIC
        src/vtohz.c
        include/vtohz.h
)
add_library(Click.VtoHz  ALIAS lib_vtohz)



target_include_directories(lib_vtohz PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_vtohz PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_vtohz PUBLIC MikroSDK.Driver)

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs4854 LANGUAGES MikroC)
else()
    project(lib_rs4854 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs4854 STATIC
        src/rs4854.c
        include/rs4854.h
)
add_library(Click.Rs4854  ALIAS lib_rs4854)



target_include_directories(lib_rs4854 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs4854 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs4854 PUBLIC MikroSDK.Driver)

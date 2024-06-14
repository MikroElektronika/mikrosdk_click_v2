cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lyra24p LANGUAGES MikroC)
else()
    project(lib_lyra24p LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lyra24p STATIC
        src/lyra24p.c
        include/lyra24p.h
)
add_library(Click.LYRA24P  ALIAS lib_lyra24p)



target_include_directories(lib_lyra24p PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lyra24p PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lyra24p PUBLIC MikroSDK.Driver)


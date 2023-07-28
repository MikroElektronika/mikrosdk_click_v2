cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_anynet2g LANGUAGES MikroC)
else()
    project(lib_anynet2g LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_anynet2g STATIC
        src/anynet2g.c
        include/anynet2g.h
)
add_library(Click.AnyNet2G  ALIAS lib_anynet2g)



target_include_directories(lib_anynet2g PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_anynet2g PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_anynet2g PUBLIC MikroSDK.Driver)

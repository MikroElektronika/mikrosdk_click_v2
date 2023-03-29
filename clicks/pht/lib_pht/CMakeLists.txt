cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pht LANGUAGES MikroC)
else()
    project(lib_pht LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pht STATIC
        src/pht.c
        include/pht.h
)
add_library(Click.PHT  ALIAS lib_pht)



target_include_directories(lib_pht PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pht PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pht PUBLIC MikroSDK.Driver)

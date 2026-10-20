cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bihall247bn LANGUAGES MikroC)
else()
    project(lib_bihall247bn LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bihall247bn STATIC
        src/bihall247bn.c
        include/bihall247bn.h
)
add_library(Click.BIHall247BN  ALIAS lib_bihall247bn)



target_include_directories(lib_bihall247bn PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bihall247bn PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bihall247bn PUBLIC MikroSDK.Driver)


cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gnss4 LANGUAGES MikroC)
else()
    project(lib_gnss4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gnss4 STATIC
        src/gnss4.c
        include/gnss4.h
)
add_library(Click.Gnss4  ALIAS lib_gnss4)



target_include_directories(lib_gnss4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gnss4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gnss4 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gnss4 PUBLIC MikroSDK.GenericPointer)

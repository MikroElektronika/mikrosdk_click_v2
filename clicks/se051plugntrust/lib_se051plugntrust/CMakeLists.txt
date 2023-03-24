cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_se051plugntrust LANGUAGES MikroC)
else()
    project(lib_se051plugntrust LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_se051plugntrust STATIC
        src/se051plugntrust.c
        include/se051plugntrust.h
)
add_library(Click.SE051PlugnTrust  ALIAS lib_se051plugntrust)



target_include_directories(lib_se051plugntrust PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_se051plugntrust PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_se051plugntrust PUBLIC MikroSDK.Driver)

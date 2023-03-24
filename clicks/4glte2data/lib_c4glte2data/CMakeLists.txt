cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c4glte2data LANGUAGES MikroC)
else()
    project(lib_c4glte2data LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c4glte2data STATIC
        src/c4glte2data.c
        include/c4glte2data.h
)
add_library(Click.4GLTE2Data  ALIAS lib_c4glte2data)



target_include_directories(lib_c4glte2data PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c4glte2data PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c4glte2data PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_c4glte2data PUBLIC MikroSDK.Conversions)

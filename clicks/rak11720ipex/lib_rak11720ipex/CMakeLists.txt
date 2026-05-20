cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rak11720ipex LANGUAGES MikroC)
else()
    project(lib_rak11720ipex LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rak11720ipex STATIC
        src/rak11720ipex.c
        include/rak11720ipex.h
)
add_library(Click.RAK11720IPEX IPEX  ALIAS lib_rak11720ipex)



target_include_directories(lib_rak11720ipex PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rak11720ipex PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rak11720ipex PUBLIC MikroSDK.Driver)


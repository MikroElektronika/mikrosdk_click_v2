cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_touchkey2 LANGUAGES MikroC)
else()
    project(lib_touchkey2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_touchkey2 STATIC
        src/touchkey2.c
        include/touchkey2.h
)
add_library(Click.Touchkey2  ALIAS lib_touchkey2)



target_include_directories(lib_touchkey2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_touchkey2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_touchkey2 PUBLIC MikroSDK.Driver)

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irgrid5 LANGUAGES MikroC)
else()
    project(lib_irgrid5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irgrid5 STATIC
        src/irgrid5.c
        include/irgrid5.h
)
add_library(Click.IRGrid5  ALIAS lib_irgrid5)



target_include_directories(lib_irgrid5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irgrid5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irgrid5 PUBLIC MikroSDK.Driver)


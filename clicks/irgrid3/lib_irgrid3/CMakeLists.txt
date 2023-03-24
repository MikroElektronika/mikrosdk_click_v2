cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irgrid3 LANGUAGES MikroC)
else()
    project(lib_irgrid3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irgrid3 STATIC
        src/irgrid3.c
        include/irgrid3.h
)
add_library(Click.IRGrid3  ALIAS lib_irgrid3)



target_include_directories(lib_irgrid3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irgrid3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irgrid3 PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})

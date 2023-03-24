cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irgrid LANGUAGES MikroC)
else()
    project(lib_irgrid LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irgrid STATIC
        src/irgrid.c
        include/irgrid.h
)
add_library(Click.IRGrid  ALIAS lib_irgrid)



target_include_directories(lib_irgrid PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irgrid PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irgrid PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})

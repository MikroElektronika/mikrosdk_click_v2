cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_irgrid2 LANGUAGES MikroC)
else()
    project(lib_irgrid2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_irgrid2 STATIC
        src/irgrid2.c
        include/irgrid2.h
)
add_library(Click.IRGrid2  ALIAS lib_irgrid2)



target_include_directories(lib_irgrid2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_irgrid2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_irgrid2 PUBLIC MikroSDK.Driver)

include(mikroeUtils)
math_check_target(${PROJECT_NAME})

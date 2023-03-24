cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_smoke LANGUAGES MikroC)
else()
    project(lib_smoke LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_smoke STATIC
        src/smoke.c
        include/smoke.h
)
add_library(Click.Smoke  ALIAS lib_smoke)



target_include_directories(lib_smoke PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_smoke PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_smoke PUBLIC MikroSDK.Driver)

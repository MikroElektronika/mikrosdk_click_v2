cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buckboost2 LANGUAGES MikroC)
else()
    project(lib_buckboost2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buckboost2 STATIC
        src/buckboost2.c
        include/buckboost2.h
)
add_library(Click.BuckBoost2  ALIAS lib_buckboost2)



target_include_directories(lib_buckboost2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buckboost2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buckboost2 PUBLIC MikroSDK.Driver)

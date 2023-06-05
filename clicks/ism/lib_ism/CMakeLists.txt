cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ism LANGUAGES MikroC)
else()
    project(lib_ism LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ism STATIC
        src/ism.c
        include/ism.h
)
add_library(Click.Ism  ALIAS lib_ism)



target_include_directories(lib_ism PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ism PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ism PUBLIC MikroSDK.Driver)

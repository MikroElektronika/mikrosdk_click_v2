cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_thermo3 LANGUAGES MikroC)
else()
    project(lib_thermo3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_thermo3 STATIC
        src/thermo3.c
        include/thermo3.h
)
add_library(Click.Thermo3  ALIAS lib_thermo3)



target_include_directories(lib_thermo3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_thermo3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_thermo3 PUBLIC MikroSDK.Driver)

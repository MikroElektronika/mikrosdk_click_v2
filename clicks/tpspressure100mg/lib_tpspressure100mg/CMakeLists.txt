cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tpspressure100mg LANGUAGES MikroC)
else()
    project(lib_tpspressure100mg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tpspressure100mg STATIC
        src/tpspressure100mg.c
        include/tpspressure100mg.h
)
add_library(Click.TPSPressure100MG  ALIAS lib_tpspressure100mg)



target_include_directories(lib_tpspressure100mg PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tpspressure100mg PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tpspressure100mg PUBLIC MikroSDK.Driver)


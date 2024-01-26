cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_accelpressure LANGUAGES MikroC)
else()
    project(lib_accelpressure LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_accelpressure STATIC
        src/accelpressure.c
        include/accelpressure.h
)
add_library(Click.AccelPressure  ALIAS lib_accelpressure)



target_include_directories(lib_accelpressure PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_accelpressure PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_accelpressure PUBLIC MikroSDK.Driver)


cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_diffpressure LANGUAGES MikroC)
else()
    project(lib_diffpressure LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_diffpressure STATIC
        src/diffpressure.c
        include/diffpressure.h
)
add_library(Click.Diffpressure  ALIAS lib_diffpressure)



target_include_directories(lib_diffpressure PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_diffpressure PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_diffpressure PUBLIC MikroSDK.Driver)

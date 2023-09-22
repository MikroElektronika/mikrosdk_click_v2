cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbuartiso LANGUAGES MikroC)
else()
    project(lib_usbuartiso LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbuartiso STATIC
        src/usbuartiso.c
        include/usbuartiso.h
)
add_library(Click.USBUARTISO  ALIAS lib_usbuartiso)



target_include_directories(lib_usbuartiso PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbuartiso PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbuartiso PUBLIC MikroSDK.Driver)


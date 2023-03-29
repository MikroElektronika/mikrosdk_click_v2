cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs4853 LANGUAGES MikroC)
else()
    project(lib_rs4853 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs4853 STATIC
        src/rs4853.c
        include/rs4853.h
)
add_library(Click.Rs4853  ALIAS lib_rs4853)



target_include_directories(lib_rs4853 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs4853 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs4853 PUBLIC MikroSDK.Driver)

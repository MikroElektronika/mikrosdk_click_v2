cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_wrls24ghz LANGUAGES MikroC)
else()
    project(lib_wrls24ghz LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_wrls24ghz STATIC
        src/wrls24ghz.c
        include/wrls24ghz.h
)
add_library(Click.WRLS24GHz  ALIAS lib_wrls24ghz)



target_include_directories(lib_wrls24ghz PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_wrls24ghz PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_wrls24ghz PUBLIC MikroSDK.Driver)


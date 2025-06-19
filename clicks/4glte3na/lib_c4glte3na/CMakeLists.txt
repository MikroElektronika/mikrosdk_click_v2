cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c4glte3na LANGUAGES MikroC)
else()
    project(lib_c4glte3na LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c4glte3na STATIC
        src/c4glte3na.c
        include/c4glte3na.h
)
add_library(Click.4GLTE3NA  ALIAS lib_c4glte3na)



target_include_directories(lib_c4glte3na PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c4glte3na PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c4glte3na PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_c4glte3na PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_c4glte3na PUBLIC MikroSDK.GenericPointer)


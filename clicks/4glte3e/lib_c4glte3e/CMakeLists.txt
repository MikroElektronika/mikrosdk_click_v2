cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c4glte3e LANGUAGES MikroC)
else()
    project(lib_c4glte3e LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c4glte3e STATIC
        src/c4glte3e.c
        include/c4glte3e.h
)
add_library(Click.4GLTE3E  ALIAS lib_c4glte3e)



target_include_directories(lib_c4glte3e PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c4glte3e PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c4glte3e PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_c4glte3e PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_c4glte3e PUBLIC MikroSDK.GenericPointer)


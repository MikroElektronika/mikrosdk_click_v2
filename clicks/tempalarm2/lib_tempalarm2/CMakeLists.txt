cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tempalarm2 LANGUAGES MikroC)
else()
    project(lib_tempalarm2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tempalarm2 STATIC
        src/tempalarm2.c
        include/tempalarm2.h
)
add_library(Click.TempAlarm2  ALIAS lib_tempalarm2)



target_include_directories(lib_tempalarm2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tempalarm2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tempalarm2 PUBLIC MikroSDK.Driver)


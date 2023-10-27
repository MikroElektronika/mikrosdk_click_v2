cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tempalarm LANGUAGES MikroC)
else()
    project(lib_tempalarm LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tempalarm STATIC
        src/tempalarm.c
        include/tempalarm.h
)
add_library(Click.TempAlarm  ALIAS lib_tempalarm)



target_include_directories(lib_tempalarm PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tempalarm PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tempalarm PUBLIC MikroSDK.Driver)


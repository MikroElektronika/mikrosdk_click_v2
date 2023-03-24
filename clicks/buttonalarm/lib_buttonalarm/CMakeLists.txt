cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buttonalarm LANGUAGES MikroC)
else()
    project(lib_buttonalarm LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buttonalarm STATIC
        src/buttonalarm.c
        include/buttonalarm.h
)
add_library(Click.ButtonAlarm  ALIAS lib_buttonalarm)



target_include_directories(lib_buttonalarm PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buttonalarm PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buttonalarm PUBLIC MikroSDK.Driver)

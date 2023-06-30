cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_temphum21 LANGUAGES MikroC)
else()
    project(lib_temphum21 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_temphum21 STATIC
        src/temphum21.c
        include/temphum21.h
)
add_library(Click.TempHum21  ALIAS lib_temphum21)



target_include_directories(lib_temphum21 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_temphum21 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_temphum21 PUBLIC MikroSDK.Driver)

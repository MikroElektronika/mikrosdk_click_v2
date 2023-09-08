cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nanobeacon LANGUAGES MikroC)
else()
    project(lib_nanobeacon LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nanobeacon STATIC
        src/nanobeacon.c
        src/nanobeacon_adv.c
        include/nanobeacon.h
        include/nanobeacon_adv.h
)
add_library(Click.NanoBeacon  ALIAS lib_nanobeacon)



target_include_directories(lib_nanobeacon PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nanobeacon PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nanobeacon PUBLIC MikroSDK.Driver)


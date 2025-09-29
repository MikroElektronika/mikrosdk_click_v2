cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mdbt42q LANGUAGES MikroC)
else()
    project(lib_mdbt42q LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mdbt42q STATIC
        src/mdbt42q.c
        include/mdbt42q.h
)
add_library(Click.MDBT42Q  ALIAS lib_mdbt42q)



target_include_directories(lib_mdbt42q PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mdbt42q PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mdbt42q PUBLIC MikroSDK.Driver)


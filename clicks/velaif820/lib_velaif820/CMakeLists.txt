cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_velaif820 LANGUAGES MikroC)
else()
    project(lib_velaif820 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_velaif820 STATIC
        src/velaif820.c
        include/velaif820.h
)
add_library(Click.VelaIF820  ALIAS lib_velaif820)



target_include_directories(lib_velaif820 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_velaif820 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_velaif820 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_velaif820 PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_velaif820 PUBLIC MikroSDK.GenericPointer)


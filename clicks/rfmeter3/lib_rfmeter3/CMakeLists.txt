cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rfmeter3 LANGUAGES MikroC)
else()
    project(lib_rfmeter3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rfmeter3 STATIC
        src/rfmeter3.c
        include/rfmeter3.h
)
add_library(Click.RFMeter3  ALIAS lib_rfmeter3)



target_include_directories(lib_rfmeter3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rfmeter3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rfmeter3 PUBLIC MikroSDK.Driver)

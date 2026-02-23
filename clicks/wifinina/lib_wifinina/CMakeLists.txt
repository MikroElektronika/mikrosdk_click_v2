cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_wifinina LANGUAGES MikroC)
else()
    project(lib_wifinina LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_wifinina STATIC
        src/wifinina.c
        include/wifinina.h
)
add_library(Click.WiFiNINA  ALIAS lib_wifinina)



target_include_directories(lib_wifinina PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_wifinina PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_wifinina PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_wifinina PUBLIC MikroSDK.GenericPointer)

cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lyra24p LANGUAGES MikroC)
else()
    project(example_lyra24p LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lyra24p
        main.c
    
)


############################ example_lyra24p GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lyra24p PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lyra24p PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lyra24p PUBLIC MikroSDK.Log)
add_subdirectory(lib_lyra24p)
target_link_libraries(example_lyra24p PUBLIC Click.LYRA24P)
############################ example_lyra24p GENERATED CODE END ###########################


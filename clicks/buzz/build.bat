
@ECHO OFF 

REM ------------------------------------------------------
REM ------------------------------------------------ Build
REM ------------------------------------------------------

set ROOT=%~dp0
set COMPILER=C:\NectoStudio\NectoStudio\compilers\ARM\mikroC\mikroCARM
set COMPILER_LIBS="C:\NectoStudio\NectoStudio\compilers\ARM\mikroC\libs"

REM ------------------------------------------------------------------------------- M0 (MCU CARD 3) STM32L073RZ
set MIKROSDK_M0="%LOCALAPPDATA%/Mikroe/NectoStudio/mikrosdk/2.0.0/FUSIONFORARMV8_STM32L073RZ" 
REM ------------------------------------------------------------------------------- M3 (MCU CARD 10) STM32F107VC
set MIKROSDK_M3="%LOCALAPPDATA%/Mikroe/NectoStudio/mikrosdk/2.0.0/FUSIONFORARMV8_STM32F107VC"
REM ------------------------------------------------------------------------------- M4 (MCU CARD) STM32F407ZG
set MIKROSDK_M4EF="%LOCALAPPDATA%/Mikroe/NectoStudio/mikrosdk/2.0.0/FUSIONFORARMV8_STM32F407ZG"
REM ------------------------------------------------------------------------------- M7 (MCU CARD 23) STM32F767BI
set MIKROSDK_M7="%LOCALAPPDATA%/Mikroe/NectoStudio/mikrosdk/2.0.0/FUSIONFORARMV8_STM32F767BI"

set MIKROSDK_LIBRARY="%ROOT%/lib"

REM -------------------------------------------- Build M0

mkdir build\m0
cd build\m0
call memake -C MEMAKE_TOOLCHAIN="%COMPILER%"
call memake -C MEMAKE_MCU_NAME=STM32L073RZ
call memake -C MEMAKE_DELAY_FREQ=32
call memake -C MEMAKE_PREFIX_PATH=%COMPILER_LIBS%;%MIKROSDK_M0%
call memake -C MEMAKE_CORE_NAME=M0
call memake -C MEMAKE_COMPILER_FLAGS="-UICD -SSA -O00000004 -DBG"
call memake -C MEMAKE_LINKER_FLAGS="-UICD -SSA -O00000004 -DBG"
call memake -C MEMAKE_DEVICES=STM32L073RZ
call memake -C MEMAKE_INSTALL_PREFIX=%ROOT%/temp/Data/build/m0
call memake --generate %MIKROSDK_LIBRARY%
call memake --build all
call memake --install
cd %ROOT%

echo "[ Build M0 ] - STM32L073RZ"

REM -------------------------------------------- Build M3

mkdir build\m3
cd build\m3
call memake -C MEMAKE_TOOLCHAIN="%COMPILER%"
call memake -C MEMAKE_MCU_NAME=STM32F107VC
call memake -C MEMAKE_DELAY_FREQ=72
call memake -C MEMAKE_PREFIX_PATH=%COMPILER_LIBS%;%MIKROSDK_M3%
call memake -C MEMAKE_CORE_NAME=M3
call memake -C MEMAKE_COMPILER_FLAGS="-UICD -SSA -O00000004 -DBG"
call memake -C MEMAKE_LINKER_FLAGS="-UICD -SSA -O00000004 -DBG"
call memake -C MEMAKE_DEVICES=STM32F107VC
call memake -C MEMAKE_INSTALL_PREFIX=%ROOT%/temp/Data/build/m3
call memake --generate %MIKROSDK_LIBRARY%
call memake --build all
call memake --install
cd %ROOT%

echo "[ Build M3 ] - STM32F107VC"

REM -------------------------------------------- Build M4EF

mkdir build\m4
cd build\m4
call memake -C MEMAKE_TOOLCHAIN="%COMPILER%"
call memake -C MEMAKE_MCU_NAME=STM32F407ZG
call memake -C MEMAKE_DELAY_FREQ=168
call memake -C MEMAKE_PREFIX_PATH=%COMPILER_LIBS%;%MIKROSDK_M4EF%
call memake -C MEMAKE_CORE_NAME=M4EF
call memake -C MEMAKE_COMPILER_FLAGS="-UICD -SSA -O00000004 -DBG"
call memake -C MEMAKE_LINKER_FLAGS="-UICD -SSA -O00000004 -DBG"
call memake -C MEMAKE_DEVICES=STM32F407ZG
call memake -C MEMAKE_INSTALL_PREFIX=%ROOT%/temp/Data/build/m4
call memake --generate %MIKROSDK_LIBRARY%
call memake --build all
call memake --install
cd %ROOT%

echo ">>> [ Build M4 ] - STM32F407ZG"

REM -------------------------------------------- Build M7

mkdir build\m7
cd build\m7
call memake -C MEMAKE_TOOLCHAIN="%COMPILER%"
call memake -C MEMAKE_MCU_NAME=STM32F767BI
call memake -C MEMAKE_DELAY_FREQ=216
call memake -C MEMAKE_PREFIX_PATH=%COMPILER_LIBS%;%MIKROSDK_M7%
call memake -C MEMAKE_CORE_NAME=M7
call memake -C MEMAKE_COMPILER_FLAGS="-UICD -SSA -O00000004 -DBG"
call memake -C MEMAKE_LINKER_FLAGS="-UICD -SSA -O00000004 -DBG"
call memake -C MEMAKE_DEVICES=STM32F767BI
call memake -C MEMAKE_INSTALL_PREFIX=%ROOT%/temp/Data/build/m7
call memake --generate %MIKROSDK_LIBRARY%
call memake --build all
call memake --install
cd %ROOT%
echo "[ Build M7 ] - STM32F767BI"

rem ________________ DELITE BUILD  _______________________

rmdir /s /q "%ROOT%/build"

REM ------------------------------------------------------
REM ---------------------------------------------- Doxygen
REM ------------------------------------------------------

mkdir ".\temp\Help\doc"

call doxygen ./doc/doxy/Doxyfile.doxy

REM ------------------------------------------------------
REM ------------------------------------------------- Copy
REM ------------------------------------------------------

rem ____________________  EXAMPLE  _______________________

set EXAMPLE=".\example"
set EXAMPLE_DESTINATION=".\temp\Examples\example"

mkdir ".\temp\Examples\example"

XCOPY %EXAMPLE% %EXAMPLE_DESTINATION% /E /y

rem ___________________  LIBRARY  _______________________

set LIBRARY=".\lib"
set LIBRARY_DESTINATION=".\temp\Data"

XCOPY %LIBRARY% %LIBRARY_DESTINATION% /E /y

rem ___________________  RESOURCES  _____________________

set DETAILS=".\DETAILS.md"
set CHANGELOG=".\CHANGELOG.md"
set CLICK_ICON=".\doc\image\click_icon.png"
set RESOURCES_DESTINATION=".\temp\Resources"
 
mkdir ".\temp\Resources"
 
COPY %DETAILS% %RESOURCES_DESTINATION% 
COPY %CHANGELOG% %RESOURCES_DESTINATION% 
COPY %CLICK_ICON% %RESOURCES_DESTINATION% 

rem ___________________  MANIFEST ______________________

set MANIFEST=".\doc\package\manifest.json"
set MANIFEST_DESTINATION=".\temp"

COPY %MANIFEST% %MANIFEST_DESTINATION% 

REM ------------------------------------------------------
REM ---------------------------------------------  Package
REM ------------------------------------------------------

mkdir ".\packages"

cd ./temp
call package_maker_command_line.exe -o ./buzz_click_package.zip -m ./manifest.json
cd ../

set PACKAGE_ZIP=".\temp\buzz_click_package.zip"
set PACKAGE_DESTINATION=".\packages"

COPY %PACKAGE_ZIP% %PACKAGE_DESTINATION% 
DEL %PACKAGE_ZIP%

REM ------------------------------------------------------

PAUSE
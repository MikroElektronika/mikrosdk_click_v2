
param (
    [Parameter(Mandatory=$true)][string]$click,
    [Parameter(Mandatory=$false)][string]$libstock
)

# ------------------------------------------------------
# -------------------------------------------- FUNCTIONS
# ------------------------------------------------------
function Get-JsonObjFromFile {
    param(
        [parameter(Mandatory = $true)]$File
    )

    $JsonObject = Get-Content $File | out-string | ConvertFrom-Json -ErrorAction Stop 
    return $JsonObject;
}

function clear_old_files{
    process
    {
        if ( $(Test-Path -Path "$CLICK_DIR\build") -eq $true )
        {
            Remove-Item "$CLICK_DIR\build" -Recurse | Out-Null
        }
        if ( $(Test-Path -Path "$CLICK_DIR\click_build") -eq $true )
        {
            Remove-Item "$CLICK_DIR\click_build" -Recurse | Out-Null
        }
        if ( $(Test-Path -Path "$CLICK_DIR\packages") -eq $true )
        {
            Remove-Item "$CLICK_DIR\packages" -Recurse | Out-Null
        }
        if ( $(Test-Path -Path "$CLICK_DIR\temp") -eq $true )
        {
            Remove-Item "$CLICK_DIR\temp" -Recurse | Out-Null
        }
        if ( $(Test-Path -Path "$CLICK_DIR\.meproject") -eq $true )
        {
            Remove-Item "$CLICK_DIR\.meproject" -Recurse | Out-Null
        }
        if ( $(Test-Path -Path "$CLICK_DIR\.meproject") -eq $true )
        {
            Remove-Item "$CLICK_DIR\.meproject" -Recurse | Out-Null
        }
        if ( $(Test-Path -Path "$CLICK_DIR\.gitignore") -eq $true )
        {
            Remove-Item "$CLICK_DIR\.gitignore" | Out-Null
        }
    }
} 

# ------------------------------------------------------
# ------------------------------------------ GLOBAL PATH
# ------------------------------------------------------

# Clear errors if using same session
$Global:Error.Clear()
$Global:LASTEXITCODE = 0
$ErrorActionPreference = "Stop"

$CLICK_DIR = "..\clicks\$click"
if ( $(Test-Path -Path $CLICK_DIR) -eq $false )
{
    Write-Host " >>> ERROR!!! - Click directory not found <<<" -ForegroundColor Red
    Exit -1
}

$COMPILER_ARM_PATH="$env:MIKROE_STUDIO_ROOT\compilers\ARM\mikroC\mikroCARM"
$COMPILER_ARM_LIBS_PATH="$env:MIKROE_STUDIO_ROOT\compilers\ARM\mikroC\libs"

$COMPILER_PIC_PATH="$env:MIKROE_STUDIO_ROOT\compilers\PIC\mikroC\mikroCPIC1618"
$COMPILER_PIC_LIBS_PATH="$env:MIKROE_STUDIO_ROOT\compilers\PIC\mikroC\libs"
$PIC_SELECTION_BUILD = "PIC18_97J94_CORTEX"
$SDK_NECTO_PATH="$env:LOCALAPPDATA\Mikroe\NectoStudio\mikrosdk\2.0.0\"



if ( $(Test-Path -Path $SDK_NECTO_PATH) -eq $false )
{
    Write-Host " >>> ERROR!!! - MikroSDK path is invalid <<<" -ForegroundColor Red
    Exit -1
}

$Targets = @( 
    'ARM_STM_M0_CORTEX', 
    'ARM_STM_M3_CORTEX',
    'ARM_STM_M4_CORTEX',
    'ARM_STM_M7_CORTEX',
    'PIC18_97J94_CORTEX'
    )

# ------------------------------------------------------
# ------------------------------------------------ Build
# ------------------------------------------------------

# Brise sve nepotrebne fajlove pre startovanja procesa
clear_old_files


    $JsonObj = Get-JsonObjFromFile -File $(Join-Path -Path $(Get-Location) -ChildPath "cortex_targets.json")

    New-Item -Path "$CLICK_DIR\build" -ItemType Directory | Out-Null
    Write-Host " >>> MikroSDK v2.0 [Build] <<<" -ForegroundColor Yellow

    New-Item -Path "$CLICK_DIR\click_build" -ItemType Directory | Out-Null
    $OUTPUT_BUILD_DIR = Join-Path -Path $PSScriptRoot -ChildPath "$CLICK_DIR\click_build"
    Set-Location -Path $OUTPUT_BUILD_DIR
 

    # ----- ARM -----
    foreach ( $Id in $Targets )
    {
        # Create folder
        New-Item -Path "$CLICK_DIR\build\$Id" -ItemType Directory | Out-Null

        $Target = $JsonObj.$Id

        if ( $id -eq $PIC_SELECTION_BUILD )
        {
            & memake -C MEMAKE_TOOLCHAIN=$COMPILER_PIC_PATH  | Out-Null
        }
        else {
            & memake -C MEMAKE_TOOLCHAIN=$COMPILER_ARM_PATH  | Out-Null
        }

        & memake -C MEMAKE_MCU_NAME=$($Target.MCU_NAME) | Out-Null
        & memake -C MEMAKE_DELAY_FREQ=$($Target.FREQ)  | Out-Null
    
        $SDK_PATH_2 = $SDK_NECTO_PATH + $Target.PREFIX_PATH

        if ( $id -eq $PIC_SELECTION_BUILD )
        {
            & memake -C MEMAKE_PREFIX_PATH=$($COMPILER_PIC_LIBS_PATH + ';' + $SDK_PATH_2)  | Out-Null
        }
        else {
            & memake -C MEMAKE_PREFIX_PATH=$($COMPILER_ARM_LIBS_PATH + ';' + $SDK_PATH_2)  | Out-Null 
        }
        
        & memake -C MEMAKE_CORE_NAME=$($Target.CORE) | Out-Null

        if ( $id -eq $PIC_SELECTION_BUILD )
        {
            & memake -C MEMAKE_COMPILER_FLAGS='-UICD -O11111114 -C -DBG' | Out-Null
            & memake -C MEMAKE_LINKER_FLAGS='-UICD -O11111114 -C -DBG'  | Out-Null
        }
        else {
            & memake -C MEMAKE_COMPILER_FLAGS='-UICD -SSA -O11111114 -C -DBG' | Out-Null
            & memake -C MEMAKE_LINKER_FLAGS='-UICD -SSA -O11111114 -C -DBG'  | Out-Null
        }
       
        & memake -C MEMAKE_DEVICES=$($Target.MCU_NAME) | Out-Null
    
        $INSTALL_PATH=$($Target.INSTALL) 
        & memake -C MEMAKE_INSTALL_PREFIX="..\$INSTALL_PATH"  | Out-Null
        
        $SDK_LIBRARY_PATH="..\lib"
        & memake --generate $SDK_LIBRARY_PATH | Out-Null
        & memake --build all  | Out-Null
        & memake --install  | Out-Null
        
        # ERROR CHACK
        if ( $LASTEXITCODE -eq 0 ) 
        {
            Write-Host " >>> Build done: $Id" -ForegroundColor Green
        }
        else 
        {
            Write-Host " >>> Build error: $Id " -ForegroundColor Red
        }
    }    

    Set-Location -Path $PSScriptRoot
    Remove-Item "$CLICK_DIR\build" -Recurse | Out-Null
    Remove-Item "$CLICK_DIR\clicks" -Recurse | Out-Null

# ------------------------------------------------------
# --------------------------------------- CHANGE VERSION
# ------------------------------------------------------

If ( $libstock -eq 'replace' )
{
    $manifest_json = Get-JsonObjFromFile -File $(Join-Path -Path $CLICK_DIR -ChildPath "doc\package\manifest.json")
    $package_version = $manifest_json.version
    $substr_pkg_ver_first = $package_version.Substring( 0, 6 )
    $substr_pkg_ver_last = $package_version.Substring( 6, ($package_version.Length - 6 ) )
    $substr_pkg_ver_int = $( $substr_pkg_ver_last -as [int] ) + 1
    $manifest_json.version = "$substr_pkg_ver_first" + "$substr_pkg_ver_int"

    $MANIFEST_FILE = $(Join-Path -Path $CLICK_DIR -ChildPath "doc\package\manifest.json")
    ( ( Get-Content -path $MANIFEST_FILE -Raw ) -replace $package_version, $manifest_json.version ) | Set-Content -Path $MANIFEST_FILE
    # $manifest_json | ConvertTo-Json | Out-File $MANIFEST_FILE 
    # Ovo je alternativni nacin ali u nasem slucaju pravi bagove....
} 
 
# ------------------------------------------------------
# -------------------------------------------- COPY DATA
# ------------------------------------------------------

Write-Host " >>> Copy data to temp directory <<<" -ForegroundColor Yellow

# ---------------------------------------------- EXAMPLE

$SOURCE_PATH ="$CLICK_DIR\example"
$DESTIONATION_PATH ="$CLICK_DIR\temp\Examples\example"

New-Item -Path "$CLICK_DIR\temp\Examples\example" -ItemType Directory | Out-Null
Copy-Item $SOURCE_PATH\* $DESTIONATION_PATH -Recurse -Force | Out-Null

# ERROR CHACK
if ( $LASTEXITCODE -eq 0 ) 
{
    Write-Host " >>> Copy [Example] done" -ForegroundColor Green
}
else 
{
    Write-Host " >>> Copy [Example] error" -ForegroundColor Red
    Exit -1
}

# ---------------------------------------------- LIBRARY

$SOURCE_PATH ="$CLICK_DIR\lib\src"
$HEADER_PATH ="$CLICK_DIR\lib\include"
$DESTIONATION_PATH ="$CLICK_DIR\temp\Examples\example"
$MEMAKE_FOR_REMOVE = "$CLICK_DIR\temp\Examples\example\memake.txt"

Copy-Item $SOURCE_PATH\* $DESTIONATION_PATH -Recurse -Force | Out-Null
Copy-Item $HEADER_PATH\* $DESTIONATION_PATH -Recurse -Force | Out-Null

Remove-Item $MEMAKE_FOR_REMOVE | Out-Null

# ERROR CHACK
if ( $LASTEXITCODE -eq 0 ) 
{
    Write-Host " >>> Copy [Library] done" -ForegroundColor Green
}
else 
{
    Write-Host " >>> Copy [Library] error" -ForegroundColor Red
    Exit -1
}

# ---------------------------------------------- MEMAKE

$MEMAKE_PATH="memake.txt"
$MEMAKE_ORIGIN_PATH="$CLICK_DIR\temp\Examples\example\memake.txt"
$MEMAKE_DESTINATION_PATH="$CLICK_DIR\temp\Examples\example"

Copy-Item $MEMAKE_PATH $MEMAKE_DESTINATION_PATH -Recurse -Force | Out-Null
( ( Get-Content -path $MEMAKE_ORIGIN_PATH -Raw ) -replace '{NAME}', $click ) | Set-Content -Path $MEMAKE_ORIGIN_PATH

# ERROR CHACK
if ( $LASTEXITCODE -eq 0 ) 
{
    Write-Host " >>> Copy [Memake create] done" -ForegroundColor Green
}
else 
{
    Write-Host " >>> Copy [Memake create] error" -ForegroundColor Red
    Exit -1
}

# ---------------------------------------------- RESOURCE

$DETAILS_PATH="$CLICK_DIR\DETAILS.md"
$CHANGELOG_PATH="$CLICK_DIR\CHANGELOG.md"
$CLICK_ICON_PATH="$CLICK_DIR\doc\image\click_icon.png"
$RESOURCES_PATH="$CLICK_DIR\temp\Resources"

New-Item -Path "$CLICK_DIR\temp\Resources" -ItemType Directory | Out-Null
Copy-Item $DETAILS_PATH $RESOURCES_PATH -Recurse -Force | Out-Null
Copy-Item $CHANGELOG_PATH $RESOURCES_PATH -Recurse -Force | Out-Null
Copy-Item $CLICK_ICON_PATH $RESOURCES_PATH -Recurse -Force | Out-Null

# ERROR CHACK
if ( $LASTEXITCODE -eq 0 ) 
{
    Write-Host " >>> Copy [Resources] done" -ForegroundColor Green
}
else 
{
    Write-Host " >>> Copy [Resources] error" -ForegroundColor Red
    Exit -1
}

# ---------------------------------------------- MANIFEST and MEMAKE

$MANIFEST_PATH="$CLICK_DIR\doc\package\manifest.json"
$MANIFEST_DESTINATION_PATH="$CLICK_DIR\temp"

Copy-Item $MANIFEST_PATH $MANIFEST_DESTINATION_PATH -Recurse -Force | Out-Null

# ERROR CHACK
if ( $LASTEXITCODE -eq 0 ) 
{
    Write-Host " >>> Copy [Manifest] done" -ForegroundColor Green
}
else 
{
    Write-Host " >>> Copy [Manifest] error" -ForegroundColor Red
    Exit -1
}

# ------------------------------------------------------
# ---------------------------------------------- DOXYGEN
# ------------------------------------------------------

Write-Host " >>> Make doxygen files <<<" -ForegroundColor Yellow

New-Item -Path "$CLICK_DIR\temp\Help\doc" -ItemType Directory | Out-Null

& doxygen "$CLICK_DIR/doc/doxy/Doxyfile.doxy" | Out-Null

# ERROR CHACK
if ( $LASTEXITCODE -eq 0 ) 
{
    Write-Host " >>> Make [Doxygen] done" -ForegroundColor Green
}
else 
{
    Write-Host " >>> Make [Doxygen] error" -ForegroundColor Red
    Exit -1
}

# ------------------------------------------------------
# ---------------------------------------------- PACKAGE
# ------------------------------------------------------

Write-Host " >>> Make a package <<<" -ForegroundColor Yellow

$PACKAGE_NAME = "$CLICK_DIR\temp\" + $click + "_package.zip" 
New-Item -Path "$CLICK_DIR\packages" -ItemType Directory | Out-Null

#Call memake for create click package 
& mepackage.exe make -o $PACKAGE_NAME -m "$CLICK_DIR\temp\manifest.json" | Out-Null

$PACKAGE_ZIP="$CLICK_DIR\temp\" + $click + "_package.zip"
$PACKAGE_DESTINATION="$CLICK_DIR\packages"

Copy-Item $PACKAGE_ZIP $PACKAGE_DESTINATION -Recurse -Force | Out-Null
Remove-Item $PACKAGE_ZIP | Out-Null

Write-Host " >>> Script done <<<" -ForegroundColor Blue

# ------------------------------------------------------
# ------------------------------------------------- DONE
# ------------------------------------------------------

if ( $libstock -eq 'upload' )
{
    Write-Host "Libstock: " $libstock -ForegroundColor Blue
}
elseif ( $libstock -eq 'replace' )
{
    Write-Host "Libstock: " $libstock -ForegroundColor Blue
    #Call memake for create click package
    #$PACKAGE_PATH = Join-Path -Path $PSScriptRoot -ChildPath "$CLICK_DIR\packages\thermo15_package.zip" 
    $PACKAGE_PATH = "$CLICK_DIR\packages\" + $click + "_package.zip" 
    & mepackage.exe upload -p $PACKAGE_PATH --update | Out-Null
    Write-Host "DONE " $libstock -ForegroundColor Yellow
}
elseif ( $libstock -eq 'none' )
{
    Write-Host "Libstock: " $libstock -ForegroundColor Blue
}
else
{
    # Pita da li je potreban upload
    Write-Host "Would you like to upolad your package." -ForegroundColor Blue
    $ask_upload = Read-Host 'Upload [U], Replace [R] or No [N] '

    if ( $ask_upload -eq 'U' ) 
    {
        Write-Host " >>> Uploading now !!!" -ForegroundColor Green
    }
    elseif ( $ask_upload -eq 'R') 
    {
        Write-Host " >>> Replacing now !!!" -ForegroundColor Green
    }
    elseif ( $ask_upload -eq 'N' )
    {
        Write-Host " >>> No uploading - finish done !!!" -ForegroundColor Green
    }
    else {
        Write-Host " >>> finish done !!!" -ForegroundColor Green
    }
}



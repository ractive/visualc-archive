@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by BLUESSON.HPJ. >"hlp\Bluesson.hm"
echo. >>"hlp\Bluesson.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\Bluesson.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\Bluesson.hm"
echo. >>"hlp\Bluesson.hm"
echo // Prompts (IDP_*) >>"hlp\Bluesson.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\Bluesson.hm"
echo. >>"hlp\Bluesson.hm"
echo // Resources (IDR_*) >>"hlp\Bluesson.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\Bluesson.hm"
echo. >>"hlp\Bluesson.hm"
echo // Dialogs (IDD_*) >>"hlp\Bluesson.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\Bluesson.hm"
echo. >>"hlp\Bluesson.hm"
echo // Frame Controls (IDW_*) >>"hlp\Bluesson.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\Bluesson.hm"
REM -- Make help for Project BLUESSON


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\Bluesson.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\Bluesson.hlp" goto :Error
if not exist "hlp\Bluesson.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\Bluesson.hlp" Debug
if exist Debug\nul copy "hlp\Bluesson.cnt" Debug
if exist Release\nul copy "hlp\Bluesson.hlp" Release
if exist Release\nul copy "hlp\Bluesson.cnt" Release
echo.
goto :done

:Error
echo hlp\Bluesson.hpj(1) : error: Problem encountered creating help file

:done
echo.

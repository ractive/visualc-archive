Name "HardLinker"
OutFile HardLinker.exe
CRCCheck on
LicenseText "Please read the license agreement before you continue"
LicenseData license.txt
ComponentText "Component"
InstType Normal
DirText "It's recommended that you install the DLL in your system directory! Leave this setting for proper functionality!"
UninstallText "Uninstall HardLinker"
UninstallExeName uninst-hl.exe
InstallDir $PROGRAMFILES\HardLinker
SetOutPath $INSTDIR
SetOverwrite on
File Release\HardLinker.dll
File ReadMe.txt
RegDLL $INSTDIR\HardLinker.dll
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\NSIS" "DisplayName" "HardLinker (remove only)"
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\NSIS" "UninstallString" '"$INSTDIR\uninst-hl.exe"'
Exec '"notepad" "$INSTDIR\ReadMe.txt"'

Section Uninstall
UnRegDLL $INSTDIR\HardLinker.dll
DeleteRegKey HKEY_CLASSES_ROOT "*\shellex\Context\MenuHandlers\HardLinker"
DeleteRegKey HKEY_CLASSES_ROOT "*\shellex\DragDropHandlers\HardLinker"
DeleteRegKey HKEY_CLASSES_ROOT "Directory\shellex\DragDropHandlers\HardLinker"
DeleteRegKey HKEY_CLASSES_ROOT "Drive\shellex\DragDropHandlers\HardLinker"
DeleteRegKey HKEY_CLASSES_ROOT "CLSID\{38998C6C-0242-4bba-94EB-214D9F49BB8B}"
Delete $INSTDIR\HardLinker.dll
Delete $INSTDIR\uninst-hl.exe
RMDir $INSTDIR

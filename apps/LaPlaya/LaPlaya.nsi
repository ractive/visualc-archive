Name "Spinner Plus"
LicenseText "Please read and agree to this license before continuing."
LicenseData license.txt
ComponentText "This will install LaPlaya on your system. Select which options you want set up."
DirText "Select a directory to install Spinner Plus in."
UninstallText "This will uninstall LaPlaya. Hit Next to uninstall, or Cancel to cancel."
UninstallExeName uninst-laplaya.exe
OutFile LaPlaya.exe
InstType Typical

InstallDir "$PROGRAMFILES\LaPlaya"
SetOverwrite on

Section "LaPlaya (required)"
	SetOutPath $INSTDIR
	File Release\LaPlaya.exe
	File ReadMe.txt
	WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\LaPlaya" "DisplayName" "LaPlaya (remove only)"
	WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\LaPlaya" "UninstallString" '"$INSTDIR\uninst-laplaya.exe"'
	WriteRegStr HKEY_CURRENT_USER "Software\@ractive Software" "LaPlaya" "LaPlaya"
SectionEnd

Section "View Readme.txt"
	SectionIn 1
	Exec '"$WINDIR\notepad.exe" "$INSTDIR\readme.txt"'
SectionEnd

Section "Add Icon to Start Menu"
	SectionIn 1
	CreateShortCut "$SMPROGRAMS\LaPlaya.lnk" "$INSTDIR\LaPlaya.exe" "" "" 0
SectionEnd

Section "Add Icon to Desktop"
	CreateShortCut "$DESKTOP\LaPlaya.lnk" "$INSTDIR\LaPlaya.exe" "" "" 0
SectionEnd

Section "Add Icon to Quicklauch Bar"
	CreateShortCut "$QUICKLAUNCH\LaPlaya.lnk" "$INSTDIR\LaPlaya.exe" "" "" 0
SectionEnd

Section "Launch LaPlaya after installation"
	Exec '"$INSTDIR\LaPlaya.exe"'
SectionEnd

Section Uninstall
	DeleteRegKey HKEY_CURRENT_USER "Software\@ractive Software\LaPlaya"
	DeleteRegKey HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\LaPlaya"

	Delete "$DESKTOP\LaPlaya.lnk"
	Delete "$SMPROGRAMS\LaPlaya.lnk"
	Delete "$QUICKLAUNCH\LaPlaya.lnk"
	Delete $INSTDIR\LaPlaya.exe
	Delete $INSTDIR\ReadMe.txt	
	RMDir $INSTDIR
	
	Delete "$SMPROGRAMS\LaPlaya.lnk"
	Delete "$DESKTOP\LaPlaya.lnk"
	Delete "$QUICKLAUNCH\LaPlaya.lnk"
SectionEnd
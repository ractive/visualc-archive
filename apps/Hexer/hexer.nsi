Name "Spinner Plus"
LicenseText "Please read and agree to this license before continuing."
LicenseData license.txt
ComponentText "This will install Hexer on your system. Select which options you want set up."
DirText "Select a directory to install Hexer in."
UninstallText "This will uninstall Hexer. Hit Next to uninstall, or Cancel to cancel."
UninstallExeName uninst-hexer.exe
OutFile Hexer.exe
InstType Typical

InstallDir "$PROGRAMFILES\Hexer"
SetOverwrite on

Section "Hexer (required)"
	SetOutPath $INSTDIR
	File Release\Hexer.exe
	File ReadMe.txt
	WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Hexer" "DisplayName" "Hexer (remove only)"
	WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\ZipAlot" "UninstallString" '"$INSTDIR\uninst-hexer.exe"'
SectionEnd

Section "View Readme.txt"
	SectionIn 1
	Exec '"$WINDIR\notepad.exe" "$INSTDIR\readme.txt"'
SectionEnd

Section "Add Icon to Start Menu"
	SectionIn 1
	CreateShortCut "$SMPROGRAMS\Hexer.lnk" "$INSTDIR\Hexer.exe" "" "" 0
SectionEnd

Section "Add Icon to Desktop"
	CreateShortCut "$DESKTOP\Hexer.lnk" "$INSTDIR\Hexer.exe" "" "" 0
SectionEnd

Section "Add Icon to Quicklauch Bar"
	CreateShortCut "$QUICKLAUNCH\Hexer.lnk" "$INSTDIR\Hexer.exe" "" "" 0
SectionEnd

Section "Launch Hexer after installation"
	Exec '"$INSTDIR\Hexer.exe"'
SectionEnd

Section Uninstall
	DeleteRegKey HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Hexer"

	Delete "$DESKTOP\Hexer.lnk"
	Delete "$SMPROGRAMS\Hexer.lnk"
	Delete "$QUICKLAUNCH\Hexer.lnk"
	Delete $INSTDIR\*.*
	RMDir $INSTDIR
	
	Delete "$SMPROGRAMS\Hexer.lnk"
	Delete "$DESKTOP\Hexer.lnk"
	Delete "$QUICKLAUNCH\Hexer.lnk"
SectionEnd
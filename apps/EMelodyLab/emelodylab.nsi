Name "EMelodyLab"
ComponentText "This will install EMelodyLab on your system. Select which options you want set up."
DirText "Select a directory to install EMelodyLab in."
UninstallText "This will uninstall EMelodyLab. Hit Next to uninstall, or Cancel to cancel."
UninstallExeName uninst-EMelodyLab.exe
OutFile EMelodyLab.exe
InstType Typical

InstallDir "$PROGRAMFILES\EMelodyLab"
SetOverwrite on

Section "EMelodyLab (required)"
	SetOutPath $INSTDIR
	File Release\EMelodyLab.exe	
	File ReadMe.txt
SectionEnd

Section "View Readme.txt"
	SectionIn 1
	Exec '"$WINDIR\notepad.exe" "$INSTDIR\readme.txt"'
SectionEnd

Section "Add Icon to Start Menu"
	SectionIn 1
	CreateShortCut "$SMPROGRAMS\EMelodyLab.lnk" "$INSTDIR\EMelodyLab.exe" "" "" 0
SectionEnd

Section "Add Icon to Desktop"
	CreateShortCut "$DESKTOP\EMelodyLab.lnk" "$INSTDIR\EMelodyLab.exe" "" "" 0
SectionEnd

Section "Add Icon to Quicklauch Bar"
	CreateShortCut "$QUICKLAUNCH\EMelodyLab.lnk" "$INSTDIR\EMelodyLab.exe" "" "" 0
SectionEnd

Section "Launch EMelodyLab after installation"
	Exec '"$INSTDIR\EMelodyLab.exe"'
SectionEnd

Section Uninstall
	Delete "$DESKTOP\EMelodyLab.lnk"
	Delete "$SMPROGRAMS\EMelodyLab.lnk"
	Delete "$QUICKLAUNCH\EMelodyLab.lnk"
	Delete $INSTDIR\*.*
	RMDir $INSTDIR
SectionEnd
;NSIS Script For Bigle 3D

!define PRODUCT "Bigle 3D"	;Define your own software name here
!define VERSION "3.40"		;Define your own software version here

;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

;--------------------------------
;Configuration

	;Do A CRC Check
	CRCCheck On

	;Compression format
	SetCompressor lzma

	;General
	Name "${PRODUCT} ${VERSION}"
	OutFile "bigle3d-${VERSION}-install.exe"

	;Folder selection page
	InstallDir "$PROGRAMFILES\${PRODUCT}"
	
	;Remember install folder
	InstallDirRegKey HKCU "Software\ALC-WBC\${PRODUCT}" ""

	;Remember the installer language
	!define MUI_LANGDLL_REGISTRY_ROOT "HKCU" 
	!define MUI_LANGDLL_REGISTRY_KEY "Software\ALC-WBC\${PRODUCT}" 
	!define MUI_LANGDLL_REGISTRY_VALUENAME "Installer Language"

;--------------------------------
;Interface Settings

	!define MUI_ABORTWARNING
	!define MUI_COMPONENTSPAGE_SMALLDESC
	!define MUI_FINISHPAGE_RUN "$INSTDIR\Bigle 3D.exe"

;--------------------------------
;Pages

	!insertmacro MUI_PAGE_WELCOME
	!insertmacro MUI_PAGE_COMPONENTS
	!insertmacro MUI_PAGE_DIRECTORY
	!insertmacro MUI_PAGE_INSTFILES
	!insertmacro MUI_PAGE_FINISH
	
	!insertmacro MUI_UNPAGE_CONFIRM
	!insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages

	!insertmacro MUI_LANGUAGE "English"
	!insertmacro MUI_LANGUAGE "French"
	
;--------------------------------
;Language Strings
		
	;Sections
	LangString SecMain ${LANG_ENGLISH} "${PRODUCT} (required)"
	LangString SecMain ${LANG_FRENCH} "${PRODUCT} (requis)"

	LangString SecShortcuts ${LANG_ENGLISH} "Start Menu + Desktop Shortcuts"
	LangString SecShortcuts ${LANG_FRENCH} "Raccourcis du Menu Démarrer + Bureau"
	
	LangString SecExamples ${LANG_ENGLISH} "Images Examples"
	LangString SecExamples ${LANG_FRENCH} "Exemples d'Images"

	;Descriptions
	LangString DESC_SecMain ${LANG_ENGLISH} "The core files required to use ${PRODUCT}"
	LangString DESC_SecMain ${LANG_FRENCH} "Fichiers principaux requis pour utiliser ${PRODUCT}"

	LangString DESC_SecExamples ${LANG_ENGLISH} "Background and relief example images files"
	LangString DESC_SecExamples ${LANG_FRENCH} "Exemples d'images de fonds et de reliefs"

	LangString DESC_SecShortcuts ${LANG_ENGLISH} "Create Start Menu and Desktop shortcuts"
	LangString DESC_SecShortcuts ${LANG_FRENCH} "Créé les raccourcis dans le menu démarrer et sur le bureau"

;--------------------------------
;Reserve Files
  
  ;These files should be inserted before other files in the data block
  ;Keep these lines before any File command
  ;Only for BZIP2 (solid) compression
  !insertmacro MUI_RESERVEFILE_LANGDLL

;--------------------------------
;Installer Sections

Section "$(SecMain)" descSecMain
	SectionIn RO

	;Install Files
	SetOutPath $INSTDIR
	File "Bigle 3D.exe"
	File "..\FreeImage.dll"
	File "History.txt"

	; Write the uninstall keys for Windows
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}" "DisplayName" "${PRODUCT}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}" "UninstallString" "$INSTDIR\Uninst.exe"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}" "DisplayIcon" "$INSTDIR\Uninst.exe"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}" "DisplayVersion" "${VERSION}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}" "Publisher" "ALC-WBC"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}" "HelpLink" "http://www.alc-wbc.com/"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}" "URLInfoAbout" "http://www.alc-wbc.com/"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}" "URLUpdateInfo" "http://www.alc-wbc.com/"
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}" "NoModify" 0x00000001
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}" "NoRepair" 0x00000001
	WriteUninstaller "$INSTDIR\Uninst.exe"
SectionEnd

Section "$(SecExamples)" descSecExamples
	;Example files
	SetOutPath $INSTDIR
	StrCmp $LANGUAGE ${LANG_ENGLISH} 0 FrenchFiles
		SetOutPath "$INSTDIR\Reliefs"
		File /oname=Fade.png "Reliefs\Dégradé.png"
		File /oname=Example1.png "Reliefs\Exemple 1.png"
		File /oname=Example2.png "Reliefs\Exemple 2.png"
		File /oname=Web_Example.png "Reliefs\Exemple du site.png"
		SetOutPath "$INSTDIR\Patterns"
		File /oname=Rainbow_130x600.png "Fonds\Arc en ciel 130x600.png"
		File /oname=Yellow-Red-Blue_Curves_155x800.png "Fonds\Courbes jaunes, rouges, bleu, etc 155x800.png"
		File /oname=Yellow-Red-Blue_degrade_with_dots_120x600.png "Fonds\Dégradé Jaune-Rouge-Bleu avec des tâches 120x600.png"
		File /oname=Dark_green_dots_114x800.png "Fonds\Point vert foncé 114x800.png"
		File /oname=Multi_color_dots_150x600.png "Fonds\Points de couleur 150x600.png"
		File /oname=Black&White_dots_150x600.png "Fonds\Points noir et blancs 150x600.png"
		File /oname=Rocks_100x195.png "Fonds\Roches 100x195.png"
		Goto EndInstall
	FrenchFiles:
		SetOutPath "$INSTDIR\Reliefs"
		File "Reliefs\Dégradé.png"
		File "Reliefs\Exemple 1.png"
		File "Reliefs\Exemple 2.png"
		File "Reliefs\Exemple du site.png"
		SetOutPath "$INSTDIR\Fonds"
		File "Fonds\Arc en ciel 130x600.png"
		File "Fonds\Courbes jaunes, rouges, bleu, etc 155x800.png"
		File "Fonds\Dégradé Jaune-Rouge-Bleu avec des tâches 120x600.png"
		File "Fonds\Point vert foncé 114x800.png"
		File "Fonds\Points de couleur 150x600.png"
		File "Fonds\Points noir et blancs 150x600.png"
		File "Fonds\Roches 100x195.png"
	EndInstall:
SectionEnd

Section "$(SecShortcuts)" descSecShortcuts
	;Add Shortcuts
	CreateDirectory "$SMPROGRAMS\${PRODUCT}"
	CreateShortCut "$SMPROGRAMS\${PRODUCT}\${PRODUCT}.lnk" "$INSTDIR\Bigle 3D.exe" "" "$INSTDIR\Bigle 3D.exe" 0

	StrCmp $LANGUAGE ${LANG_ENGLISH} 0 +2
		CreateShortCut "$SMPROGRAMS\${PRODUCT}\Change Log.lnk" "$INSTDIR\History.txt" "" "$INSTDIR\History.txt" 0
	StrCmp $LANGUAGE ${LANG_FRENCH} 0 +2
		CreateShortCut "$SMPROGRAMS\${PRODUCT}\Historique.lnk" "$INSTDIR\History.txt" "" "$INSTDIR\History.txt" 0

	StrCmp $LANGUAGE ${LANG_ENGLISH} 0 +2
		CreateShortCut "$SMPROGRAMS\${PRODUCT}\Uninstall.lnk" "$INSTDIR\Uninst.exe" "" "$INSTDIR\Uninst.exe" 0
	StrCmp $LANGUAGE ${LANG_FRENCH} 0 +2
		CreateShortCut "$SMPROGRAMS\${PRODUCT}\Déinstaller.lnk" "$INSTDIR\Uninst.exe" "" "$INSTDIR\Uninst.exe" 0

	;Desktop
	CreateShortCut "$DESKTOP\${PRODUCT}.lnk" "$INSTDIR\${PRODUCT}.exe" "" "$INSTDIR\Bigle 3D.exe" 0
SectionEnd

;--------------------------------
;Installer Functions

Function .onInit

	!insertmacro MUI_LANGDLL_DISPLAY

FunctionEnd

;--------------------------------
;Descriptions

!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
	!insertmacro MUI_DESCRIPTION_TEXT ${descSecMain} $(DESC_SecMain)
	!insertmacro MUI_DESCRIPTION_TEXT ${descSecExamples} $(DESC_SecExamples)
	!insertmacro MUI_DESCRIPTION_TEXT ${descSecShortcuts} $(DESC_SecShortcuts)
!insertmacro MUI_FUNCTION_DESCRIPTION_END
 
;--------------------------------
;Uninstaller Section

Section Uninstall
	;Delete Files
	Delete "$INSTDIR\Bigle 3D.exe"
	Delete "$INSTDIR\FreeImage.dll"
	Delete "$INSTDIR\History.txt"
	Delete "$INSTDIR\Reliefs\*.png"
	Delete "$INSTDIR\Fonds\*.png"
	Delete "$INSTDIR\Patterns\*.png"
	Delete "$DESKTOP\Bigle 3D.lnk"

	;Delete Start Menu Shortcuts
	Delete "$SMPROGRAMS\${PRODUCT}\*.*"
	RmDir "$SMPROGRAMS\${PRODUCT}"

	;Delete Uninstaller And Unistall Registry Entries
	Delete "$INSTDIR\Uninst.exe"
	DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}"
	RmDir "$INSTDIR\Reliefs"
	RmDir "$INSTDIR\Patterns"
	RmDir "$INSTDIR\Fonds"
	RmDir "$INSTDIR"

	DeleteRegKey /ifempty HKCU "Software\ALC-WBC\${PRODUCT}"
SectionEnd

;--------------------------------
;Uninstaller Functions

Function un.onInit

	!insertmacro MUI_UNGETLANGUAGE
  
FunctionEnd

; VINATEXT INSTALLER

#define MyAppName "VinaText"
#define MyAppVersion "1.0.9"
#define MyAppPublisher "vinadevs"
#define MyAppURL "https://www.vinatext.com"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{97D8E29D-3293-406A-8BA5-B855E4880CE8}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName=..\VinaText-{#MyAppVersion}
UsePreviousAppDir=no
DefaultGroupName={#MyAppName}
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputDir=..\VinaText\Installer
OutputBaseFilename=vinatext_setup_x64_{#MyAppVersion}
Compression=lzma
SolidCompression=yes
WizardStyle=modern
SetupIconFile=..\VinaText\VinaTextPortable{#MyAppVersion}\VinaText.ico
UninstallDisplayIcon={app}\VinaText.exe

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
Name: StartAfterInstall; Description: Run application after install

[Icons]
Name: "{group}\Vinatext"; Filename: "{app}\VinaText.exe"; IconFilename: "{app}\VinaText.ico"
Name: "{commondesktop}\Vinatext"; Filename: "{app}\VinaText.exe"; Tasks: desktopicon; IconFilename: "{app}\VinaText.ico"

; NOTE: Replace Source path when need to update version
[Files]
Source: "..\VinaText\VinaTextPortable{#MyAppVersion}\*"; DestDir: "{app}\"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Run]
Filename: {app}\VinaText.exe; Flags: shellexec postinstall skipifsilent nowait; Tasks: StartAfterInstall

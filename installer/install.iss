; Default Klavier installer setup
; Update for Universal C Runtime required
; https://support.microsoft.com/en-us/help/2999226/update-for-universal-c-runtime-in-windows

#define AppName "Klavier"
#define AppVersion "0.1.0"
#define AppExecutable "Klavier.exe"

[Setup]
AppName={#AppName}
AppVersion={#AppVersion}
DefaultDirName={pf}\{#AppName}
DefaultGroupName={#AppName}
UninstallDisplayIcon={app}\{#AppExecutable}
Compression=lzma2
SolidCompression=yes
WizardSmallImageFile=icon.bmp
AppPublisher=Richard "Richdark" Filipčík
AppPublisherURL=http://richdark.github.io/klavier
UninstallDisplayName={#AppName}
LicenseFile=../license.txt

[Files]
Source: "{#AppExecutable}"; DestDir: "{app}"
Source: "settings.json"; DestDir: "{app}"
Source: "vcredist_x86.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall

[Tasks]
Name: DesktopShortcut; Description: "Create desktop shortcut."
Name: RunAtStartup; Description: "Automatically run {#AppName} when Windows starts."

[Icons]
Name: "{group}\{#AppName}"; Filename: "{app}\{#AppExecutable}"
Name: "{userdesktop}\{#AppName}"; Filename: "{app}\{#AppExecutable}"; Tasks: DesktopShortcut
Name: "{userstartup}\{#AppName}"; Filename: "{app}\{#AppExecutable}"; Tasks: RunAtStartup

[Run]
Filename: "{tmp}\vcredist_x86.exe"; Check: VCRedistNeedsInstall

[Code]
{ W - Unicode }
{ A - ANSI    }
#IFDEF UNICODE
  #DEFINE AW "W"
#ELSE
  #DEFINE AW "A"
#ENDIF

type
  INSTALLSTATE = Longint;

 const
  INSTALLSTATE_INVALIDARG = -2;  { An invalid parameter was passed to the function. }
  INSTALLSTATE_UNKNOWN = -1;     { The product is neither advertised or installed. }
  INSTALLSTATE_ADVERTISED = 1;   { The product is advertised but not installed. }
  INSTALLSTATE_ABSENT = 2;       { The product is installed for a different user. }
  INSTALLSTATE_DEFAULT = 5;      { The product is installed for the current user. }

  { Visual C++ Redistributable for Visual Studio 2015 Update 3 (14.0.24215) }
  VC_2015_REDIST_X86_URL = 'http://download.microsoft.com/download/6/A/A/6AA4EDFF-645B-48C5-81CC-ED5963AEAD48/vc_redist.x86.exe';
  VC_2015_REDIST_X64_URL = 'http://download.microsoft.com/download/6/A/A/6AA4EDFF-645B-48C5-81CC-ED5963AEAD48/vc_redist.x64.exe';
  VC_2015_REDIST_X86 = '{BBF2AC74-720C-3CB3-8291-5E34039232FA}';
  VC_2015_REDIST_X64 = '{50A2BC33-C9CD-3BF1-A8FF-53C10A0B183C}';

function MsiQueryProductState(szProduct: string): INSTALLSTATE; 
  external 'MsiQueryProductState{#AW}@msi.dll stdcall';

function VCVersionInstalled(const ProductID: string): Boolean;
begin
  Result := MsiQueryProductState(ProductID) = INSTALLSTATE_DEFAULT;
end;

function VCRedistNeedsInstall: Boolean;
begin
  Result := not (VCVersionInstalled(VC_2015_REDIST_X86));
end;

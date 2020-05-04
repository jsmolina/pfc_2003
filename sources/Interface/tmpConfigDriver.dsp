# Microsoft Developer Studio Project File - Name="tmpConfigDriver" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=tmpConfigDriver - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tmpConfigDriver.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tmpConfigDriver.mak" CFG="tmpConfigDriver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tmpConfigDriver - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "tmpConfigDriver - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tmpConfigDriver - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I ".\head" /I "C:\Archivos de programa\3Dconnexion\3DxWare SDK\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc0a /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc0a /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 wrapper.lib dinput8.lib dxguid.lib /nologo /subsystem:windows /incremental:yes /machine:I386 /out:"./Release/ConfigDriver.exe"

!ELSEIF  "$(CFG)" == "tmpConfigDriver - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I ".\head" /I "C:\Archivos de programa\3Dconnexion\3DxWare SDK\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc0a /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0xc0a /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wrapper.lib dinput8.lib dxguid.lib /nologo /subsystem:windows /debug /machine:I386 /out:"./Debug/ConfigDriver.exe" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "tmpConfigDriver - Win32 Release"
# Name "tmpConfigDriver - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\head\AsignBotons.cpp
# End Source File
# Begin Source File

SOURCE=.\head\AsignEixos.cpp
# End Source File
# Begin Source File

SOURCE=.\head\AsignEspecials.cpp
# End Source File
# Begin Source File

SOURCE=.\head\Boto.cpp
# End Source File
# Begin Source File

SOURCE=.\head\CBDades.cpp
# End Source File
# Begin Source File

SOURCE=.\head\CConfiguration.cpp
# End Source File
# Begin Source File

SOURCE=.\head\DirectInput\CDInputJoystick.cpp
# End Source File
# Begin Source File

SOURCE=.\head\DirectInput\CDInputMouse.cpp
# End Source File
# Begin Source File

SOURCE=.\head\DirectInput\CDirectInput.cpp
# End Source File
# Begin Source File

SOURCE=.\head\CFilterDI.cpp
# End Source File
# Begin Source File

SOURCE=.\head\CurrentStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\head\DirectInput\dinput_f.cpp
# End Source File
# Begin Source File

SOURCE=.\head\Eix.cpp
# End Source File
# Begin Source File

SOURCE=.\head\Event.cpp
# End Source File
# Begin Source File

SOURCE=.\head\Handle.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Tab1.cpp
# End Source File
# Begin Source File

SOURCE=.\Tab2.cpp
# End Source File
# Begin Source File

SOURCE=.\Tab3.cpp
# End Source File
# Begin Source File

SOURCE=.\Tab4.cpp
# End Source File
# Begin Source File

SOURCE=.\Tab5.cpp
# End Source File
# Begin Source File

SOURCE=.\Tab6.cpp
# End Source File
# Begin Source File

SOURCE=.\tmpConfigDriver.cpp
# End Source File
# Begin Source File

SOURCE=.\tmpConfigDriver.rc
# End Source File
# Begin Source File

SOURCE=.\tmpConfigDriverDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\head\Window_Handles.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\head\Asignacio.h
# End Source File
# Begin Source File

SOURCE=.\head\AsignBotons.h
# End Source File
# Begin Source File

SOURCE=.\head\AsignEixos.h
# End Source File
# Begin Source File

SOURCE=.\head\AsignEspecials.h
# End Source File
# Begin Source File

SOURCE=.\head\Boto.h
# End Source File
# Begin Source File

SOURCE=.\head\CBDades.h
# End Source File
# Begin Source File

SOURCE=.\head\CConfiguration.h
# End Source File
# Begin Source File

SOURCE=.\head\DirectInput\CDInputJoystick.h
# End Source File
# Begin Source File

SOURCE=.\head\DirectInput\CDInputMouse.h
# End Source File
# Begin Source File

SOURCE=.\head\DirectInput\CDirectInput.h
# End Source File
# Begin Source File

SOURCE=.\head\CFilterDI.h
# End Source File
# Begin Source File

SOURCE=.\head\CurrentStatus.h
# End Source File
# Begin Source File

SOURCE=.\head\DirectInput\dinput_f.h
# End Source File
# Begin Source File

SOURCE=.\head\Eix.h
# End Source File
# Begin Source File

SOURCE=.\head\Event.h
# End Source File
# Begin Source File

SOURCE=.\exports.h
# End Source File
# Begin Source File

SOURCE=.\head\Handle.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Tab1.h
# End Source File
# Begin Source File

SOURCE=.\Tab2.h
# End Source File
# Begin Source File

SOURCE=.\Tab3.h
# End Source File
# Begin Source File

SOURCE=.\Tab4.h
# End Source File
# Begin Source File

SOURCE=.\Tab5.h
# End Source File
# Begin Source File

SOURCE=.\Tab6.h
# End Source File
# Begin Source File

SOURCE=.\tmpConfigDriver.h
# End Source File
# Begin Source File

SOURCE=.\tmpConfigDriverDlg.h
# End Source File
# Begin Source File

SOURCE=.\head\Window_Handles.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\tmpConfigDriver.ico
# End Source File
# Begin Source File

SOURCE=.\res\tmpConfigDriver.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project

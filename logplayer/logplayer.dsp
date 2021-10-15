# Microsoft Developer Studio Project File - Name="logplayer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=logplayer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "logplayer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "logplayer.mak" CFG="logplayer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "logplayer - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "logplayer - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "logplayer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /I "$(QTDIR)\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /D "MicWindows" /YX /FD /c
# ADD BASE RSC /l 0x816 /d "NDEBUG"
# ADD RSC /l 0x816 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(QTDIR)\lib\qt-mt230nc.lib $(QTDIR)\lib\qtmain.lib ws2_32.lib /nologo /subsystem:windows /incremental:yes /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "logplayer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "$(QTDIR)\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "QT_DLL" /D "QT_THREAD_SUPPORT" /D "MicWindows" /YX /FD /GZ /c
# ADD BASE RSC /l 0x816 /d "_DEBUG"
# ADD RSC /l 0x816 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib $(QTDIR)\lib\qt-mt230nc.lib $(QTDIR)\lib\qtmain.lib ws2_32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "logplayer - Win32 Release"
# Name "logplayer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\cbbeacon.cpp
# End Source File
# Begin Source File

SOURCE=.\cbclient.cpp
# End Source File
# Begin Source File

SOURCE=.\cbgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\cbgridhandler.cpp
# End Source File
# Begin Source File

SOURCE=.\cblab.cpp
# End Source File
# Begin Source File

SOURCE=.\cblabhandler.cpp
# End Source File
# Begin Source File

SOURCE=.\cbloghandler.cpp
# End Source File
# Begin Source File

SOURCE=.\cblogplayer.cpp
# End Source File
# Begin Source File

SOURCE=.\cbparameters.cpp
# End Source File
# Begin Source File

SOURCE=.\cbparamhandler.cpp
# End Source File
# Begin Source File

SOURCE=.\cbpoint.cpp
# End Source File
# Begin Source File

SOURCE=.\cbposition.cpp
# End Source File
# Begin Source File

SOURCE=.\cbreceptionhandler.cpp
# End Source File
# Begin Source File

SOURCE=.\cbreceptionist.cpp
# End Source File
# Begin Source File

SOURCE=.\cbrobot.cpp
# End Source File
# Begin Source File

SOURCE=.\cbtarget.cpp
# End Source File
# Begin Source File

SOURCE=.\cbview.cpp
# End Source File
# Begin Source File

SOURCE=.\cbviewhandler.cpp
# End Source File
# Begin Source File

SOURCE=.\cbwall.cpp
# End Source File
# Begin Source File

SOURCE=.\logplayer.cpp
# End Source File
# Begin Source File

SOURCE=.\logplayerGUI.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_cblogplayer.cpp
# End Source File
# Begin Source File

SOURCE=.\moc_logplayerGUI.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\cbbeacon.h
# End Source File
# Begin Source File

SOURCE=.\cbclient.h
# End Source File
# Begin Source File

SOURCE=.\cbgrid.h
# End Source File
# Begin Source File

SOURCE=.\cbgridhandler.h
# End Source File
# Begin Source File

SOURCE=.\cblab.h
# End Source File
# Begin Source File

SOURCE=.\cblabhandler.h
# End Source File
# Begin Source File

SOURCE=.\cbloghandler.h
# End Source File
# Begin Source File

SOURCE=.\cblogplayer.h

!IF  "$(CFG)" == "logplayer - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\cblogplayer.h
InputName=cblogplayer

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "logplayer - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Moc'ing $(InputName).h ...
InputDir=.
InputPath=.\cblogplayer.h
InputName=cblogplayer

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cbparameters.h
# End Source File
# Begin Source File

SOURCE=.\cbparamhandler.h
# End Source File
# Begin Source File

SOURCE=.\cbpoint.h
# End Source File
# Begin Source File

SOURCE=.\cbposition.h
# End Source File
# Begin Source File

SOURCE=.\cbreceptionform.h
# End Source File
# Begin Source File

SOURCE=.\cbreceptionhandler.h
# End Source File
# Begin Source File

SOURCE=.\cbreceptionist.h
# End Source File
# Begin Source File

SOURCE=.\cbrobot.h
# End Source File
# Begin Source File

SOURCE=.\cbtarget.h
# End Source File
# Begin Source File

SOURCE=.\cbview.h
# End Source File
# Begin Source File

SOURCE=.\cbviewcommand.h
# End Source File
# Begin Source File

SOURCE=.\cbviewhandler.h
# End Source File
# Begin Source File

SOURCE=.\cbwall.h
# End Source File
# Begin Source File

SOURCE=.\logplayerGUI.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\logplayerGUI.ui

!IF  "$(CFG)" == "logplayer - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\logplayerGUI.ui
InputName=logplayerGUI

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "logplayer - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Uic'ing $(InputName).ui ...
InputDir=.
InputPath=.\logplayerGUI.ui
InputName=logplayerGUI

BuildCmds= \
	%qtdir%\bin\uic.exe $(InputPath) -o $(InputDir)\$(InputName).h \
	%qtdir%\bin\uic.exe $(InputPath) -i $(InputName).h -o $(InputDir)\$(InputName).cpp \
	%qtdir%\bin\moc.exe $(InputDir)\$(InputName).h -o $(InputDir)\moc_$(InputName).cpp \
	

"$(InputDir)\$(InputName).h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"$(InputDir)\moc_$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project

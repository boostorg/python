# Microsoft Developer Studio Project File - Name="bpl_static" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=bpl_static - Win32 DebugPython
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bpl_static.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bpl_static.mak" CFG="bpl_static - Win32 DebugPython"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bpl_static - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "bpl_static - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "bpl_static - Win32 DebugPython" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bpl_static - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W4 /WX /GR /GX /O2 /I "..\..\.." /I "c:\tools\python\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "bpl_static - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /WX /Gm /GR /GX /Zi /Od /I "..\..\.." /I "c:\tools\python\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "bpl_static - Win32 DebugPython"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "bpl_static___Win32_DebugPython"
# PROP BASE Intermediate_Dir "bpl_static___Win32_DebugPython"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugPython"
# PROP Intermediate_Dir "DebugPython"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /WX /Gm /GR /GX /Zi /Od /I "..\..\.." /I "c:\tools\python\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /WX /Gm /GR /GX /Zi /Od /I "..\..\.." /I "c:\tools\python\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "BOOST_DEBUG_PYTHON" /FR /YX /FD /GZ /EHs /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "bpl_static - Win32 Release"
# Name "bpl_static - Win32 Debug"
# Name "bpl_static - Win32 DebugPython"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\classes.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=..\src\conversions.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=..\src\extension_class.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=..\src\functions.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=..\src\init_function.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=..\src\module_builder.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=..\src\objects.cpp
# ADD CPP /W3
# End Source File
# Begin Source File

SOURCE=..\src\types.cpp
# ADD CPP /W3
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\boost\python\detail\base_object.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\callback.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\caller.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\detail\cast.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\class_builder.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\classes.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\detail\config.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\conversions.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\errors.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\detail\extension_class.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\detail\functions.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\detail\init_function.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\module_builder.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\detail\none.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\objects.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\operators.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\reference.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\detail\signatures.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\detail\singleton.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\detail\types.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\boost\python\detail\wrap_python.hpp
# End Source File
# End Group
# End Target
# End Project

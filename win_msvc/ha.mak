# Microsoft Developer Studio Generated NMAKE File, Based on ha.dsp
!IF "$(CFG)" == ""
CFG=ha - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ha - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ha - Win32 Release" && "$(CFG)" != "ha - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ha.mak" CFG="ha - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ha - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ha - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ha - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ha.exe"


CLEAN :
	-@erase "$(INTDIR)\acoder.obj"
	-@erase "$(INTDIR)\archive.obj"
	-@erase "$(INTDIR)\asc.obj"
	-@erase "$(INTDIR)\cpy.obj"
	-@erase "$(INTDIR)\dirent.obj"
	-@erase "$(INTDIR)\error.obj"
	-@erase "$(INTDIR)\ha.obj"
	-@erase "$(INTDIR)\haio.obj"
	-@erase "$(INTDIR)\hsc.obj"
	-@erase "$(INTDIR)\info.obj"
	-@erase "$(INTDIR)\machine.obj"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\swdict.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ha.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../include" /I "../win_msvc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\ha.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ha.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\ha.pdb" /machine:I386 /out:"$(OUTDIR)\ha.exe" 
LINK32_OBJS= \
	"$(INTDIR)\acoder.obj" \
	"$(INTDIR)\archive.obj" \
	"$(INTDIR)\asc.obj" \
	"$(INTDIR)\cpy.obj" \
	"$(INTDIR)\error.obj" \
	"$(INTDIR)\ha.obj" \
	"$(INTDIR)\haio.obj" \
	"$(INTDIR)\hsc.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\swdict.obj" \
	"$(INTDIR)\machine.obj" \
	"$(INTDIR)\dirent.obj" \
	"$(INTDIR)\info.obj"

"$(OUTDIR)\ha.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ha - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ha.exe"


CLEAN :
	-@erase "$(INTDIR)\acoder.obj"
	-@erase "$(INTDIR)\archive.obj"
	-@erase "$(INTDIR)\asc.obj"
	-@erase "$(INTDIR)\cpy.obj"
	-@erase "$(INTDIR)\dirent.obj"
	-@erase "$(INTDIR)\error.obj"
	-@erase "$(INTDIR)\ha.obj"
	-@erase "$(INTDIR)\haio.obj"
	-@erase "$(INTDIR)\hsc.obj"
	-@erase "$(INTDIR)\info.obj"
	-@erase "$(INTDIR)\machine.obj"
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\swdict.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ha.exe"
	-@erase "$(OUTDIR)\ha.ilk"
	-@erase "$(OUTDIR)\ha.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "../include" /I "../win_msvc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\ha.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ  /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ha.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\ha.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ha.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\acoder.obj" \
	"$(INTDIR)\archive.obj" \
	"$(INTDIR)\asc.obj" \
	"$(INTDIR)\cpy.obj" \
	"$(INTDIR)\error.obj" \
	"$(INTDIR)\ha.obj" \
	"$(INTDIR)\haio.obj" \
	"$(INTDIR)\hsc.obj" \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\swdict.obj" \
	"$(INTDIR)\machine.obj" \
	"$(INTDIR)\dirent.obj" \
	"$(INTDIR)\info.obj"

"$(OUTDIR)\ha.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ha.dep")
!INCLUDE "ha.dep"
!ELSE 
!MESSAGE Warning: cannot find "ha.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ha - Win32 Release" || "$(CFG)" == "ha - Win32 Debug"
SOURCE=..\c\acoder.c

"$(INTDIR)\acoder.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\c\archive.c

"$(INTDIR)\archive.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\c\asc.c

"$(INTDIR)\asc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\c\cpy.c

"$(INTDIR)\cpy.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\win_msvc\dirent.c

"$(INTDIR)\dirent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\c\error.c

"$(INTDIR)\error.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\c\ha.c

"$(INTDIR)\ha.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\c\haio.c

"$(INTDIR)\haio.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\c\hsc.c

"$(INTDIR)\hsc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\win_msvc\info.c

"$(INTDIR)\info.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\win_msvc\machine.c

"$(INTDIR)\machine.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\c\misc.c

"$(INTDIR)\misc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\c\swdict.c

"$(INTDIR)\swdict.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


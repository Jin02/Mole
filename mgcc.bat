@echo off
REM	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
REM
REM		ELF MAKE BATCH FILE
REM
REM
REM		[usage]
REM			mgcc[.bat]
REM	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

@echo off
set path=D:\Program Files\WIPI SDK\bin;D:\Program Files\WIPI SDK\tools/H-i686-pc-cygwin/bin;%path%
rm -rf obj/*.o
make --win32 -f WIPIModuleGcc.mak

if ERRORLEVEL 1 goto ERROR

goto COMPLETE

:USAGE
echo =============================================================================
echo 사용법:
echo   mgcc[.bat]
echo =============================================================================
goto END

:COMPLETE
echo .
echo =============================================================================
echo 파일이 생성되었습니다.
echo =============================================================================
echo                                     - Bye! -
if "%1" == "" goto exit
start wrunt.exe /PROJECT=D:\Program Files\WIPI SDK\Projects\Mole\Mole.xwp /Auto /TYPE=daf /INSTALL 
cmd.exe
goto exit

:ERROR
echo .
echo =============================================================================
echo 파일을 생성할 수 없습니다.
echo =============================================================================


:END
echo                                     - Bye! -
if "%1" == "" goto exit
cmd.exe
:exit
@echo on

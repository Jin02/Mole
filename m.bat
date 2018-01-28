@echo off
REM	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
REM
REM		ELF MAKE BATCH FILE
REM
REM	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
REM
REM		[usage]
REM			m[.bat]
REM
REM	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
set path=D:\Program Files\WIPI SDK\bin;%path%
rm -rf obj/*.o
make --win32 -f WIPIModule.mak

if ERRORLEVEL 1 goto ERROR

goto COMPLETE

:USAGE
echo =============================================================================
echo 사용법:
echo   m[.bat]
echo =============================================================================
goto END

:COMPLETE
echo .
echo =============================================================================
echo 파일이 생성되었습니다.
echo =============================================================================
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

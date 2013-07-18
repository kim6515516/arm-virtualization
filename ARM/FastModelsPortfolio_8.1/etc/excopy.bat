@echo Copying Fast Models Portfolio examples to local user writable space

@REM Only Vista & Win7 - version string 6.0 and 6.1
@for /f "tokens=1,2,3* delims=\]\[" %%a in ('ver') do set WINVS=%%b
@echo %WINVS%
@for /f "tokens=1,2,3* delims=. " %%a in ("%WINVS%") do set WINV=%%b
@echo %WINV%

@if %WINV% LSS 6 (
    @echo This is not needed on Windows XP or earlier
    @exit /B 0
)

@if [%1]==[] goto error_no_PVLIB_HOME
@if "%USERPROFILE%"=="" goto error_no_USER_HOME

@for %%A IN ("%PVLIB_HOME%") do (
    @set "TGTDIR=%%~nxA"
)

@set PVLH=%1

@for /f "useback tokens=*" %%a in ('%PVLH%') do set PVLH=%%~a

@if exist "%USERPROFILE%\ARM\%TGTDIR%\examples" goto error_target_exists

mkdir "%USERPROFILE%\ARM\%TGTDIR%\examples"
xcopy "%PVLH%\examples" "%USERPROFILE%\ARM\%TGTDIR%\examples\" /q /e /d

@exit /B 0

@REM -----------------------------------------------------------------------
:error_target_exists
@echo ERROR: Cannot copy to User directory - target already exists
@echo Please copy Fast Models Examples directory to a user writable location
@goto end

@REM -----------------------------------------------------------------------
:error_no_USER_HOME
@echo ERROR: Cannot determine the location of the User directory.
@echo Please copy Fast Models Examples directory to a user writable location
@goto end

@REM -----------------------------------------------------------------------
:error_no_PVLIB_HOME
@echo ERROR: Cannot determine the location of the Fast Models Portfolio install.
@echo Please copy Fast Models Examples directory to a user writable location
@goto end

:end

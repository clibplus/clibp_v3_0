@echo off 2> null

ls /bin >$null 2>&1; sudo make; exit 0 # DO STUFF IN THE PARATHENSIS AS FUNCTION ( WINDOWS IGNORES THIS )

if "%OS%"=="Windows_NT" call :setup_fsl
goto :eof

:setup_fsl

@echo [31mSetting up FSL for Windows[0m
del $null
del null

cl >nul 2>&1
if errorlevel 0 (
    echo [32mMSVC Already Installed and Setup![0m
    exit /b 1
)

for /f "delims=" %%A in ('where /r C:\ VsDevCmd.bat 2^>nul') do set "test=%%A"

if not defined test (
    echo MSVC Dev Setup Not Found!!
    exit /b 1
)


echo [32mSetting up MSVC Variables![0m

call "%test%" -arch=x64

@REM if exist "C:\Program Files\Microsoft Visual Studio\" (
@REM     echo MSVC Installed.
@REM ) else (
@REM     echo MSVC Compiler Not Found!
@REM     exit /b 1
@REM )

exit /b

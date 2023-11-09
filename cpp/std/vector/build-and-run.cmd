REM "setlocal" is a safeguard required if you call this script multiple times.
REM because otherwise vcvarscall.bat will put duplicate entries in ENV variables
setlocal

REM By using "vcvarsall" it is not required to use the "Developer PowerShell for VS XXXX" or "x64 Native Tools Command Prompt for VS 2022" shells.
REM See: https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line


call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64

cls

set CURRENT_SCRIPT_DIR=%~dp0

REM ************************************************
REM  Current script location
REM ************************************************

pushd %CURRENT_SCRIPT_DIR%

IF EXIST tmp RMDIR /S /Q tmp

REM ************************************************
REM  Sample
REM ************************************************

IF EXIST build RMDIR /S /Q build

REM generate
cmake ^
  -A x64 ^
  -DCMAKE_INSTALL_PREFIX=%CURRENT_SCRIPT_DIR%\tmp ^
  -S . ^
  -B build

REM build
REM note "release" is required because "cmake --install" uses this version to install
cmake --build build --config Release
REM alternative way:
REM   cd build
REM   msbuild sample-client.sln /p:Configuration=Release
REM   cd ..

REM install for debug
cmake --install build

REM ************************************************
REM  Run
REM ************************************************

REM open the program in another window, wait and keep it open
start /wait cmd /k %CURRENT_SCRIPT_DIR%\tmp\bin\StdVectorApp.exe


REM ************************************************
REM  Uninstall everything
REM ************************************************

IF EXIST build RMDIR /S /Q build

IF EXIST tmp RMDIR /S /Q tmp

popd

endlocal

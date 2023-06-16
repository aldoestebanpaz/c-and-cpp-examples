REM "setlocal" is a safeguard required if you call this script multiple times.
REM because otherwise vcvarscall.bat will put duplicate entries in ENV variables
setlocal

REM By using "vcvarsall" it is not required to use the "Developer PowerShell for VS XXXX" or "x64 Native Tools Command Prompt for VS 2022" shells.
REM See: https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line


call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64

cls

msbuild SimpleNamedPipe.sln /p:OutDir=build

start .\Server\build\Server.exe
start .\Client\build\Client.exe

endlocal

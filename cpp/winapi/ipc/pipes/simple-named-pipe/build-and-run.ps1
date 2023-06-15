
# By using "vcvarsall" it is not required to use the "Developer PowerShell for VS XXXX" or "x64 Native Tools Command Prompt for VS 2022" shells.
# See: https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line

# Invokes a Cmd.exe shell script and updates the environment.
# Copied from https://stackoverflow.com/questions/41399692/running-a-build-script-after-calling-vcvarsall-bat-from-powershell
function Invoke-CmdScript {
  param(
    [String] $scriptName
  )
  $cmdLine = """$scriptName"" $args & set"
  & $Env:SystemRoot\system32\cmd.exe /c $cmdLine |
  select-string '^([^=]*)=(.*)$' | foreach-object {
    $varName = $_.Matches[0].Groups[1].Value
    $varValue = $_.Matches[0].Groups[2].Value
    set-item Env:$varName $varValue
  }
}

Invoke-CmdScript "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64

msbuild SimpleNamedPipe.sln /p:OutDir=build

Start-Process .\Server\build\Server.exe
Start-Process .\Client\build\Client.exe

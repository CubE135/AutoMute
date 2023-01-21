@echo off
copy ..\Builds\x64\Release\auto_mute_win64.dll plugins\
copy ..\Builds\x86\Release\auto_mute_win32.dll plugins\
set /p build="Build number: "
mkdir releases\%build%
"D:\7-Zip\7z.exe" a releases\%build%\auto_mute_%build%.ts3_plugin -tzip -mx=9 -mm=Deflate ./package.ini plugins/*
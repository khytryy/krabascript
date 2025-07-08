@echo off
setlocal enabledelayedexpansion

net session >nul 2>&1
if %errorlevel% neq 0 (
    echo requesting administrator access...
    powershell -Command "Start-Process -FilePath '%~f0' -Verb runAs"
    exit /b
)

set i=0
for /d %%u in (C:\Users\*) do (
    set "folderName=%%~nu"
    if /i not "!folderName!"=="All Users" if /i not "!folderName!"=="Default" if /i not "!folderName!"=="Default User" if /i not "!folderName!"=="Public" if /i not "!folderName!"=="krabascript" (
        set /a i+=1
        set "user[!i!]=!folderName!"
    )
)

if %i%==0 (
    echo no valid user folders found in C:\Users
    pause
    exit /b 1
)

echo for who you want to install ks?
echo tip: you can type exit to exit...
echo.

for /l %%j in (1,1,%i%) do (
    echo %%j. !user[%%j]!
)

echo.

:choice
set /p choice=choose user (1-%i%): 

if not defined user[%choice%] (
    if /i "%selectedUser%"=="exit" (
        exit /b 0
    ) else (
        echo invalid choice!
        goto choice
    )
)

set "selectedUser=!user[%choice%]!"

mkdir "C:\Users\%selectedUser%\krabascript"
cd "C:\Users\%selectedUser%\krabascript"
wget https://khytryy.neocities.org/krabascript/wgetfiles/ks.ico

reg add "HKCR\.ks" /ve /d "KSFile" /f
reg add "HKCR\KSFile" /ve /d "Krabascript file" /f
reg add "HKCR\KSFile\DefaultIcon" /ve /d "C:\Users\%selectedUser%\krabascript\ks.ico" /f

taskkill /f /im explorer.exe
ping -n 2 127.0.0.1 >nul
start explorer.exe

echo < krabascript has been installed >

pause
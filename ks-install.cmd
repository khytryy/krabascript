@echo off
setlocal enabledelayedexpansion

net session >nul 2>&1
if %errorlevel% neq 0 (
    echo requesting administrator access...
    powershell -Command "Start-Process -FilePath '%~f0' -Verb runAs"
    exit /b
)

mkdir "C:\Program Files\krabascript"
cd "C:\Program Files\krabascript"
wget https://khytryy.neocities.org/krabascript/wgetfiles/ks.ico

mkdir "bin"

reg add "HKCR\.ks" /ve /d "KSFile" /f
reg add "HKCR\KSFile" /ve /d "Krabascript file" /f
reg add "HKCR\KSFile\DefaultIcon" /ve /d "C:\Program Files\krabascript\ks.ico" /f

taskkill /f /im explorer.exe
ping -n 2 127.0.0.1 >nul
start explorer.exe

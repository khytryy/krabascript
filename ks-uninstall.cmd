@echo off
setlocal enabledelayedexpansion

net session >nul 2>&1
if %errorlevel% neq 0 (
    echo requesting administrator access...
    powershell -Command "Start-Process -FilePath '%~f0' -Verb runAs"
    exit /b
)

rd /s /q "C:\Program Files\krabascript"

reg delete "HKCR\.ks" /f
reg delete "HKCR\KSFile" /f

taskkill /f /im explorer.exe
ping -n 2 127.0.0.1 >nul
start explorer.exe

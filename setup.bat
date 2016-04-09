@echo off

Powershell.exe -executionpolicy remotesigned -File  setup.ps1

cd Plugin\External
7z\7za.exe x -aos *.7z

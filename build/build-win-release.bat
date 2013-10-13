@echo off

:: This builds Blind Crossword Editor using qmake, msvc2012 and jom.

:: Assume the .pro file exists in the parent directory
SET PROJECT_PATH=../
SET PROJECT_FILE=Blind-Crossword-Editor.pro

:: Use qmake to generate makefiles
qmake.exe %PROJECT_PATH%/%PROJECT_FILE% -r -spec win32-msvc2012 "CONFIG+=release"

:: Set MSVC environmental variables
call vcvars32.bat

:: Do the debug build using jom
jom.exe -f Makefile.Release
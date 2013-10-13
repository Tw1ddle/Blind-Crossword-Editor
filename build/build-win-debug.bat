@echo off

:: This builds Blind Crossword Editor using qmake, msvc2012 and jom.

:: Assume the .pro file exists in the parent directory
SET PROJECT_PATH=../
SET PROJECT_FILE=Blind-Crossword-Editor.pro

:: Run qmake to create makefiles
qmake.exe %PROJECT_PATH%/%PROJECT_FILE% -r -spec win32-msvc2012 "CONFIG+=debug" "CONFIG+=declarative_debug" "CONFIG+=qml_debug"

:: Set MSVC environmental variables
call vcvars32.bat

:: Do the debug build using jom
jom.exe -f Makefile.Debug
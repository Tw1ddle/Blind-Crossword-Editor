# This builds Blind Crossword Editor using qmake, g++ and make.

# Assume the .pro file exists in the parent directory
PROJECT_PATH=../
PROJECT_FILE=Blind-Crossword-Editor.pro

# Use qmake to generate makefiles
qmake $PROJECT_PATH/$PROJECT_FILE -r -spec linux-g++ CONFIG+=debug CONFIG+=declarative_debug CONFIG+=qml_debug

# Do the debug build using jom
make -r -w Makefile.Debug
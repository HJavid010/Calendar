# How to Compile
The recommended compiler is g++ from gcc\
## Install g++ And make
For Windows use MinGW and install g++ and make\
(after installing put C:\msys64\ucrt64\bin and
C:\msys64\usr\bin to system environment variable "Path")
## Compile with make
command `make` will compile and put the app in bin folder
you can also use `make run` to run immediately after compile **but remember that it will run that it will run it parent directory instead and event file well be saved there**
### Cleaning .d Files
`make cleandep`
### Cleaning All Compile Related Files
`make clean`\
**This will delete all compile app, object files and .d files for a clean build**
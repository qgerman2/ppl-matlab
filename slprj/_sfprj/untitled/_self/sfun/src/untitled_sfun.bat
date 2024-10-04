@echo off
set COMPILER=C:\MATLAB\mingw81\bin\gcc
                set CXXCOMPILER=C:\MATLAB\mingw81\bin\g++
                set COMPFLAGS=-c -fexceptions -fno-omit-frame-pointer -m64 -DMATLAB_MEX_FILE  -DMATLAB_MEX_FILE 
                set CXXCOMPFLAGS=-c -fexceptions -fno-omit-frame-pointer -m64 -DMATLAB_MEX_FILE  -DMATLAB_MEX_FILE 
                set OPTIMFLAGS=-O2 -fwrapv -DNDEBUG
                set DEBUGFLAGS=-g
                set LINKER=C:\MATLAB\mingw81\bin\gcc
                set CXXLINKER=C:\MATLAB\mingw81\bin\g++
                set LINKFLAGS=-m64 -Wl,--no-undefined -shared -static -L"C:\Program Files\MATLAB\R2024a\extern\lib\win64\mingw64" -llibmx -llibmex -llibmat -lm -llibmwlapack -llibmwblas -llibMatlabDataArray -llibMatlabEngine -Wl,"C:\Program Files\MATLAB\R2024a/extern/lib/win64/mingw64/mexFunction.def"
                set LINKDEBUGFLAGS=-g
                set NAME_OUTPUT= -o "%OUTDIR%%MEX_NAME%%MEX_EXT%"
set PATH=C:\MATLAB\mingw81\bin;C:\Program Files\MATLAB\R2024a\extern\include\win64;C:\Program Files\MATLAB\R2024a\extern\include;C:\Program Files\MATLAB\R2024a\simulink\include;C:\Program Files\MATLAB\R2024a\lib\win64;%MATLAB_BIN%;%PATH%
set INCLUDE=C:\MATLAB\mingw81\include;C:\MATLAB\mingw81\lib\gcc\x86_64-w64-mingw32\8.1.0\include\c++;C:\MATLAB\mingw81\lib\gcc\x86_64-w64-mingw32\8.1.0\include;C:\MATLAB\mingw81\lib\gcc\x86_64-w64-mingw32\8.1.0\include\c++\x86_64-w64-mingw32;C:\MATLAB\mingw81\lib\gcc\x86_64-w64-mingw32\8.1.0\include\c++\backward;C:\MATLAB\mingw81\x86_64-w64-mingw32\include;%INCLUDE%
set LIB=C:\MATLAB\mingw81\lib;;%LIB%
set LIBPATH=C:\Program Files\MATLAB\R2024a\extern\lib\win64;%LIBPATH%

gmake SHELL="cmd" -f untitled_sfun.gmk

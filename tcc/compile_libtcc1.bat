@echo off
if %~1.==. (
	set TCC=tcc
) else (
	set TCC=%~1
)

:: Get tcc architecture
%TCC% -v > temp.txt
set /p TCC_VERSION=<temp.txt
del temp.txt
for /f "tokens=4 delims=( " %%a in ("%TCC_VERSION%") do set TCC_ARCHITECTURE=%%a
echo tcc architecture: "%TCC_ARCHITECTURE%"

:: Create "lib" folder if it doesn't exist
if not exist "lib" mkdir lib
echo on

%TCC% -c lib_libtcc1/libtcc1.c
%TCC% -c lib_libtcc1/crt1.c
%TCC% -c lib_libtcc1/crt1w.c
%TCC% -c lib_libtcc1/wincrt1.c
%TCC% -c lib_libtcc1/wincrt1w.c
%TCC% -c lib_libtcc1/dllcrt1.c
%TCC% -c lib_libtcc1/dllmain.c

@if %TCC_ARCHITECTURE% == x86_64 GOTO x86_64
@if %TCC_ARCHITECTURE% == i386 GOTO i386
@if %TCC_ARCHITECTURE% == arm GOTO arm

echo Unknown architecture of tcc: "%TCC_ARCHITECTURE%"!
GOTO clean

:x86_64
%TCC% -c lib_libtcc1/chkstk.S
%TCC% -w -c lib_libtcc1/bcheck.c
%TCC% -c lib_libtcc1/alloca86_64.S
%TCC% -c lib_libtcc1/alloca86_64-bt.S
%TCC% -ar lib/libtcc1-arm.a libtcc1.o crt1.o crt1w.o wincrt1.o wincrt1w.o dllcrt1.o dllmain.o chkstk.o bcheck.o alloca86_64.o alloca86_64-bt.o
@GOTO clean

:i386
%TCC% -c lib_libtcc1/chkstk.S
%TCC% -w -c lib_libtcc1/bcheck.c
%TCC% -c lib_libtcc1/alloca86.S
%TCC% -c lib_libtcc1/alloca86-bt.S
%TCC% -ar lib/libtcc1-arm.a libtcc1.o crt1.o crt1w.o wincrt1.o wincrt1w.o dllcrt1.o dllmain.o chkstk.o bcheck.o alloca86.o alloca86-bt.o
@GOTO clean

:arm
%TCC% -c lib_libtcc1/alloca-arm.S
%TCC% -c lib_libtcc1/armeabi.c
%TCC% -c lib_libtcc1/armflush.c
%TCC% -ar lib/libtcc1-arm.a libtcc1.o crt1.o crt1w.o wincrt1.o wincrt1w.o dllcrt1.o dllmain.o alloca-arm.o armeabi.o armflush.o
@GOTO clean

:clean
del *.o
rmdir /s /q lib_libtcc1
::del %TCC%.exe

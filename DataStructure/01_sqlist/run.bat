@echo off

rem 切换到可执行文件所在目录
cd /d "%~dp0"

rem 切换控制台代码页为 UTF-8（允许 echo 正确显示 UTF-8 字符）
chcp 65001 >nul

rem 输出可执行到子目录
set "EXE=main.exe"
set "OUT_DIR=bin"

if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"

rem echo Compiling with g++...
g++ -O2 -Wall -std=c++11 -o "%OUT_DIR%\%EXE%" *.cpp
if %ERRORLEVEL% NEQ 0 (
    echo 编译失败
    exit /b %ERRORLEVEL%
)

rem echo 编译成功，运行："%OUT_DIR%\%EXE%" ...
rem echo =================================
"%OUT_DIR%\%EXE%"
rem echo =================================
rem pause

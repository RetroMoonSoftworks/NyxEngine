@echo off

mkdir ..\..\build
pushd ..\..\build
cl  -Zi ..\nyxengine\code\win32_nyx.cpp user32.lib gdi32.lib
popd

@echo off
set BOOST_INCLUDE=D:\Programming\Libraries\boost-cvs\boost
set out=_%1.cpp
if "%2" == "--multiple" set out=_%1
rem python ../src/pyste.py %2 -I%BOOST_INCLUDE -I../example --module=%1 --out=%out ../example/%1.pyste  
pyste %2 -I%BOOST_INCLUDE -I../example --module=%1 --out=%out ../example/%1.pyste   

scons --quiet multiple=%2 %1.dll

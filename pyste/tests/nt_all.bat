@echo off
call nt_build_all.bat
runtests.py
call nt_clean.bat
call nt_build_all.bat --multiple
runtests.py
call nt_clean.bat 

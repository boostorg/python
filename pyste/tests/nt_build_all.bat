@echo off

call nt_build_pyste.bat basic %1
call nt_build_pyste.bat enums %1 
call nt_build_pyste.bat header_test %1 
call nt_build_pyste.bat nested %1 
call nt_build_pyste.bat operators %1 
call nt_build_pyste.bat smart_ptr %1 
call nt_build_pyste.bat templates %1 
call nt_build_pyste.bat unions %1 
call nt_build_pyste.bat virtual %1 
call nt_build_pyste.bat virtual2 %1 
call nt_build_pyste.bat wrappertest %1 
call nt_build_pyste.bat opaque %1 

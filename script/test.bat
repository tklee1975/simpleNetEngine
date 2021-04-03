@echo off
cls
echo ================================================
echo.  
echo Test Script
echo.  
echo ================================================
echo.
echo Choice your test 
echo [1] core
echo [2] network 
echo [3] Main App 
echo [*] quit 

set bin_path=.\vs2019\

set choice=
set /p choice=Enter your choice: 
echo Your choice is %choice%

if '%choice%' == '1' goto test_core
if '%choice%' == '2' goto test_net
if '%choice%' == '3' goto main_app

goto end 

:test_core
echo Testing CoreLib
%bin_path%\Library\CoreLib\test\Debug\core_test.exe
goto end 

:test_net
echo Testing Network 
%bin_path%\Library\NetEngine\test\Debug\net_engine_test.exe
goto end 

:main_app
echo Testing Main App
%bin_path%\Debug\app1.exe
goto end 

:end 
pause 



REM arg count testing 
set /a args_count=0 
for %%A in (%*) do set /a args_count+=1 
REM echo %args_count%   

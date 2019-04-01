@echo off

REM This script will start all the services with good parameters

REM set MODE=Debug
REM set MODE=.
set MODE=..\..\..\build\bin\Debug
set RELEASE==..\..\..\build\bin\Release

rem AS
rem start %MODE%\admin_service.exe --fulladminname=admin_executor_service --shortadminname=AES
rem wait 2s (yes, i didn't find a better way to wait N seconds)
rem ping -n 2 127.0.0.1 > NUL 2>&1

rem  ras
rem start %MODE%\admin_service --fulladminname=admin_service --shortadminname=AS --writepid
rem ping -n 2 127.0.0.1 > NUL 2>&1

start %MODE%\naming_service.exe

rem wait 2s (yes, i didn't find a better way to wait N seconds)
ping -n 2 127.0.0.1 > NUL 2>&1

start %MODE%\persistent_service

rem wait 2s (yes, i didn't find a better way to wait N seconds)
rem ping -n 2 127.0.0.1 > NUL 2>&1


rem wait 2s (yes, i didn't find a better way to wait N seconds)
rem ping -n 2 127.0.0.1 > NUL 2>&1

rem start %RELEASE%\mail_service
rem start %MODE%\mail_service

rem wait 2s (yes, i didn't find a better way to wait N seconds)
rem ping -n 2 127.0.0.1 > NUL 2>&1

rem start %RELEASE%\ranking_service

rem wait 2s (yes, i didn't find a better way to wait N seconds)
ping -n 2 127.0.0.1 > NUL 2>&1


start %MODE%\schedule_service

rem wait 2s (yes, i didn't find a better way to wait N seconds)
ping -n 2 127.0.0.1 > NUL 2>&1

start %MODE%\game_service

rem wait 2s (yes, i didn't find a better way to wait N seconds)
ping -n 2 127.0.0.1 > NUL 2>&1

start %MODE%\frontend_service

rem wait 2s (yes, i didn't find a better way to wait N seconds)
ping -n 2 127.0.0.1 > NUL 2>&1

start %MODE%\logger_service



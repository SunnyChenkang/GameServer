@echo off

REM This script will kill all the services launched by shard_start.bat

taskkill /IM _service_daemon.exe /F

rem  ns
taskkill /IM frontend_service.exe /F

rem  fes
taskkill /IM game_service.exe /F

rem  egs
taskkill /IM naming_service.exe /F

rem  zs
taskkill /IM persistent_service.exe /F

rem  pds
taskkill /IM schedule_service.exe /F

rem  pds
taskkill /IM logger_service.exe /F

call _del_log.bat

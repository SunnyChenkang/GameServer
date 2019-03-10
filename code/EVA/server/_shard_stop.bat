@echo off

REM This script will kill all the services launched by shard_start.bat

taskkill /IM _service_daemon.exe /F

rem  ls
taskkill /IM login_center.exe /F

rem  ls
taskkill /IM login_center.exe /F

rem  ns
taskkill /IM naming_service.exe /F

rem  fes
taskkill /IM frontend_service.exe /F

rem  egs
taskkill /IM entities_game_service.exe /F

rem  zs
taskkill /IM player_logic_service.exe /F

rem  pds
taskkill /IM persistant_data_service.exe /F

rem  aes
taskkill /IM admin_service.exe /F

rem  mail
taskkill /IM mail_service.exe /F

taskkill /IM ranking_service.exe /F
taskkill /IM logger_service.exe /F

call _del_log.bat

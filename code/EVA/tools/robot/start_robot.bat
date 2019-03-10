@echo off
setlocal enabledelayedexpansion

set username=test

for /l %%i in (1,1,3) do (
rem echo !bz%%i!
ping -n 1 127.0.0.1 > NUL 2>&1
start robot account=%%%i
)



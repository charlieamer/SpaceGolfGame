@echo OFF
echo Params: %*
cd %~dp0
call runtime.bat
cd runtime
..\Debug\SpaceGolfGame.exe %*
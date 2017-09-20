@echo OFF
echo Params: %*
cd %~dp0
cd runtime
..\Debug\SpaceGolfGame.exe %*
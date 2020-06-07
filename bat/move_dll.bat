@echo off

pushd %~dp0
pushd ..

for %%I in ( .\DLLs\*.dll ) do (
	xcopy %%I .\x64\Debug\ /F /Y
)

popd 
popd

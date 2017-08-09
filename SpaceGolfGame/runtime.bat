mkdir .\runtime\Assets
mkdir .\runtime\levels
mkdir .\runtime\shaders
mkdir .\runtime\gui
xcopy .\Assets .\runtime\Assets /E /Y
xcopy .\levels .\runtime\levels /E /Y
xcopy .\shaders .\runtime\shaders /E /Y
xcopy .\gui .\runtime\gui /E /Y
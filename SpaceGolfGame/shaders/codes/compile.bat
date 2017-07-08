shaderc -f only_color/fs_only_color.sc -o ../glsl/fs_only_color.bin --type f -i .
shaderc -f only_color/vs_only_color.sc -o ../glsl/vs_only_color.bin --type v -i .
shaderc -f textured/fs_textured.sc -o ../glsl/fs_textured.bin --type f -i .
shaderc -f textured/vs_textured.sc -o ../glsl/vs_textured.bin --type v -i .
pause
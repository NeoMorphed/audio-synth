@echo off


set obj="bin-int/debug/"
set executable="bin/debug/audio_synth"
set pdb="bin/debug"

set start=%time%

set debug = -d

set codePaths= src/main.cpp src/core/Core.cpp src/rendering/Rendering.cpp 

set Libs= glfw3.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Ws2_32.lib iphlpapi.lib
set CompilerFlags= /nologo /JMC /Oi /WX /wd4100 /wd4458 /wd4127 /wd4996 /wd4201 /wd4189 /wd4505 /wd4700 /wd4312 /Od /MP /W4 /D_ITERATOR_DEBUG_LEVEL=2 /diagnostics:column /MDd /EHsc -Zi 
rem set obj_path=bin-int/debug/*.obj

REM /d2cgsummary
rem src/*.c src/vendor/stb_image/*.cpp src/vendor/imgui/*.cpp src/vendor/imguizmo/*.cpp
rem Only need to compile these files if compiler options change
rem cl /c %CompilerFlags% /Fo%obj% /Fe%executable% /Fd%pdb% /I dependencies/include /I src /I dependencies/include/physx /I src/vendor/imgui src/*.c src/vendor/stb_image/*.cpp src/vendor/imgui/*.cpp src/vendor/imguizmo/*.cpp
set obj_path=bin-int/debug/
set linker_input= %obj_path%pch.obj %obj_path%glad.obj %obj_path%stb_image.obj %obj_path%imgui.obj %obj_path%imgui_demo.obj %obj_path%imgui_draw.obj %obj_path%imgui_impl_glfw.obj %obj_path%imgui_impl_opengl3.obj %obj_path%imgui_tables.obj %obj_path%imgui_widgets.obj 
if [%1] == [] GOTO DEBUG
if %1 == -r GOTO RELEASE

:DEBUG
echo debug
cl %CompilerFlags% /Fo%obj% /Fe%executable% /Yupch.h /Fd%pdb% /I src /I dependencies/include %codePaths% /D __WINDOWS__ /D _CRT_SECURE_NO_WARNINGS /link /ignore:4099 /LIBPATH:dependencies/lib %Libs% %linker_input%
GOTO END

:RELEASE
echo release
set obj="bin-int/release/"
set executable="bin/release/audio_synth"
set pdb="bin/release"
set CompilerFlags= /nologo /JMC /Oi /WX /wd4100 /wd4458 /wd4127 /wd4996 /wd4201 /wd4189 /wd4505 /wd4700 /wd4312 /O2 /MP /W4 /diagnostics:column /MT /EHsc -Zi 
cl %CompilerFlags% /Fo%obj% /Fe%executable% /Yupch.h /I src %codePaths% /D __WINDOWS__  /link /ignore:4099 /LIBPATH:dependencies/lib %Libs% bin-int/release/pch.obj

:END
set level=%errorLevel%

if NOT "%1" == "-run" exit /b 2

if %level% == 0 run.bat


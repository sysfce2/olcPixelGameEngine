#!/usr/bin/bash

clang++ -I.. -o DemoKeyboard-glut DemoKeyboard.cpp -O2 -lglut -lGL -lm -lpng -lstdc++fs -std=c++20 -DOLC_PLATFORM_GLUT

clang++ -I.. -o DemoKeyboard-xlib DemoKeyboard.cpp -O2 -lX11 -lGL -lm -lpthread -lpng -lstdc++fs -std=c++20

em++ -I.. -o DemoKeyboard.html DemoKeyboard.cpp -O2 -s ALLOW_MEMORY_GROWTH=1 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2 -s USE_LIBPNG=1 -std=c++20 --preload-file assets@assets

x86_64-w64-mingw32-g++ -I.. -o DemoKeyboard.exe DemoKeyboard.cpp -luser32 -lgdi32 -lopengl32 -lgdiplus -lshlwapi -ldwmapi -lstdc++fs -std=c++20 -static
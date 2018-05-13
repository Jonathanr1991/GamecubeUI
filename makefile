dolphinboxloader:
	g++ -o dbl COSC439.cpp `pkg-config --cflags --libs sdl2`
install:
	mv bash_profile ~/.bash_profile


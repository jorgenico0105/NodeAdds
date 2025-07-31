CXXFLAGS = \
	-std=c++23 \
	-I$(HOME)/opt/raylib-5.5_linux_amd64/include \
	-I$(HOME)/opt/node/include/node \
	-Wall \
	-Wextra \
	-shared \
	-fPIC

LIBS = \
	-L$(HOME)/opt/raylib-5.5_linux_amd64/lib \
	-l:libraylib.a \
	-lm -ldl -lpthread -lGL -lX11

hello.node: hello.cpp
	g++ $(CXXFLAGS) -o hello.node hello.cpp $(LIBS)


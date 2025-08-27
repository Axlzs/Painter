CXX = g++
CXXFLAGS = -std=c++20 -I/usr/include/SDL3_image `pkg-config --cflags sdl3`
LDFLAGS = `pkg-config --libs sdl3` -lSDL3_image
TARGET = painter
TARGETDEL = painter.txt
SOURCES = main.cpp mouse.cpp canvas.cpp ui.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETDEL) $(OBJECTS)

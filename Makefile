CXX = g++
CXXFLAGS = -std=c++20 $(shell pkg-config --cflags sdl3 sdl3-image sdl3-ttf)
LDFLAGS  = $(shell pkg-config --libs sdl3 sdl3-image sdl3-ttf)
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

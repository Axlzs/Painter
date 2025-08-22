CXX = g++
CXXFLAGS = -std=c++20 `pkg-config --cflags sdl3`
LDFLAGS = `pkg-config --libs sdl3`
TARGET = painter
TARGETDEL = painter.txt
SOURCES = main.cpp mouse.cpp canvas.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETDEL) $(OBJECTS)

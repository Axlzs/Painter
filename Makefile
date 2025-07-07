CXX = g++
CXXFLAGS = -std=c++17 `pkg-config --cflags sdl3`
LDFLAGS = `pkg-config --libs sdl3`
TARGET = painter

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

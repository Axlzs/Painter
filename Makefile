GTESTDIR := external/googletest
SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin

EXE      := $(BIN_DIR)/painter
SRC      := $(wildcard $(SRC_DIR)/*.cpp)
OBJ      := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CXX      := g++
CXXFLAGS := -std=c++20 -MMD -MP \
            $(shell pkg-config --cflags sdl3 sdl3-image sdl3-ttf) \
            -Iinclude -isystem $(GTESTDIR)/include
LDFLAGS  := $(shell pkg-config --libs sdl3 sdl3-image sdl3-ttf)

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) -rv $(EXE) $(OBJ_DIR)

-include $(OBJ:.o=.d)

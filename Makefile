CXX      := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -O3 -std=c++11
LDFLAGS  := -L/usr/lib -lstdc++ -lm -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lboost_filesystem -lboost_system
BUILD    := build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
RES_DIR  := $(APP_DIR)/res
TARGET   := program
INCLUDE  := -Iinclude/
SRC      :=                      \
	$(wildcard src/*.cpp)         \

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(RES_DIR)
	@cp -r res/* $(RES_DIR)

clean:
	rm -rf build/*
                     

CXX = g++
SHELL := cmd
CXXFLAGS = -Wall -O2 -std=c++23 -mwindows

SRC = src/main.cpp src/window/procedure.cpp src/window/window.cpp src/window/fonts.cpp src/ui/sidebar.cpp
OBJ = $(SRC:src/%.cpp=obj/%.o)
TARGET = bin/main.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

obj/%.o: src/%.cpp
	@if not exist obj mkdir obj
	@if not exist obj\ui mkdir obj\ui
	@if not exist obj\window mkdir obj\window
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del $(TARGET) 2>nul || del /s /q obj\*

# HW5 makefile
EXE=HW5
SRC_DIR=src
INC_DIR=include
BUILD_DIR=build

# Main target
all: $(BUILD_DIR)/$(EXE)

# Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW -I$(INC_DIR)
LIBS=-lfreeglut -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -rf $(BUILD_DIR)/*
else
# OSX
ifeq "$(shell uname)" "Darwin"
RES=$(shell uname -r | sed -E 's/(.).*/\1/' | tr 12 21)
ARCH=$(shell uname -m)
# Check if the architecture is arm64 and link to the correct include directory (homebrew for freeglut)
ifeq ($(ARCH),arm64)
CFLG=-O3 -Wall -Wno-deprecated-declarations -I/opt/homebrew/include -arch arm64 -DRES=$(RES) -I$(INC_DIR)
else
CFLG=-O3 -Wall -Wno-deprecated-declarations -I/usr/local/include -DRES=$(RES) -I$(INC_DIR)
endif
LIBS=-framework GLUT -framework OpenGL
# Linux/Unix/Solaris
else
CFLG=-O3 -Wall -I$(INC_DIR)
LIBS=-lglut -lGLU -lGL -lm
endif
CLEAN=rm -rf $(BUILD_DIR)/*
endif

# Object files
OBJS=$(BUILD_DIR)/main.o $(BUILD_DIR)/scene.o $(BUILD_DIR)/tree.o $(BUILD_DIR)/speeder.o $(BUILD_DIR)/util.o

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile and link
$(BUILD_DIR)/$(EXE): $(OBJS)
	g++ $(CFLG) -o $@ $^ $(LIBS)

# Compile rule for each .cpp file
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/scene.hpp $(INC_DIR)/tree.hpp | $(BUILD_DIR)
	g++ -c $(CFLG) $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/scene.o: $(SRC_DIR)/scene.cpp $(INC_DIR)/scene.hpp | $(BUILD_DIR)
	g++ -c $(CFLG) $(SRC_DIR)/scene.cpp -o $(BUILD_DIR)/scene.o

$(BUILD_DIR)/tree.o: $(SRC_DIR)/tree.cpp $(INC_DIR)/tree.hpp | $(BUILD_DIR)
	g++ -c $(CFLG) $(SRC_DIR)/tree.cpp -o $(BUILD_DIR)/tree.o
	
$(BUILD_DIR)/speeder.o: $(SRC_DIR)/speeder.cpp $(INC_DIR)/speeder.hpp | $(BUILD_DIR)
	g++ -c $(CFLG) $(SRC_DIR)/speeder.cpp -o $(BUILD_DIR)/speeder.o

$(BUILD_DIR)/util.o: $(SRC_DIR)/util.cpp $(INC_DIR)/util.hpp | $(BUILD_DIR)
	g++ -c $(CFLG) $(SRC_DIR)/util.cpp -o $(BUILD_DIR)/util.o

# Clean
clean:
	$(CLEAN)
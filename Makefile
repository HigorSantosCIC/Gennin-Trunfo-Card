# Compiler and flags
CC = gcc
CFLAGS = -g -lm -Isrc/include  # Include path to header files in src/include

# Directories
SRC_DIR = src
OBJ_DIR = src/obj
BIN_DIR = src/bin

# Ensure the binary and object directories exist
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

# Source files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/funct.c $(SRC_DIR)/list.c $(SRC_DIR)/log.c $(SRC_DIR)/ninja.c

# Object files
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/funct.o $(OBJ_DIR)/list.o $(OBJ_DIR)/log.o $(OBJ_DIR)/ninja.o

# Target executable
TARGET = $(BIN_DIR)/prog.exe

# Rule to build the final executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# Rules to build object files from source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean rule
clean:
	-rm -f $(OBJ_DIR)/*.o $(TARGET)

# PHONY targets
.PHONY: clean

# Add a dependency rule for the executable to force rebuilding if a source file changes
$(TARGET): $(SRCS)

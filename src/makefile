CC := clang++
CFLAGS := -std=c++11 -Wall -o3 -g

BUILD_DIR  := bin
SOURCE_DIR := src

OBJ :=  	$(BUILD_DIR)/os.o\
	   	$(BUILD_DIR)/main.o
BIN := main

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

all: $(BIN)
$(BIN): $(OBJ)
	$(CC) -o $(BUILD_DIR)/$(BIN) $(OBJ) $(LIBS)
clean:
	rm -f $(OBJ) $(BIN)

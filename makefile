CXX = g++
CC = gcc

CXXFLAGS = -Iinclude
CFLAGS = -Iinclude

LDFLAGS = -lglfw -lGL -ldl

CPP_SRC := $(shell find src -name "*.cpp")
C_SRC   := $(shell find src -name "*.c")

OBJ := $(CPP_SRC:.cpp=.o) $(C_SRC:.c=.o)

TARGET = app.out

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
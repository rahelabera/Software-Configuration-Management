CC = g++
CFLAGS = -Iinclude -Wall
SRC = src/math_functions.cpp src/string_functions.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = my_project

all: $(TARGET)

$(TARGET): $(OBJ)
    $(CC) $(OBJ) -o $(TARGET)

%.o: %.cpp
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ) $(TARGET)

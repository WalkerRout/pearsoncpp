CC = g++
OBJS = src/*.cpp
OBJ = bin/pearsoncpp
CFLAGS = -std=gnu++20
LIBS = 

all: run

build:
	@$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $(OBJ)

run: build
	@./$(OBJ)

clean:
	@rm ./$(OBJ)
	@echo "Cleaned!"

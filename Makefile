# Makefile - Library Management System
# Author: Himesh Khatri <Khatrihimesh2@gmail.com> | +91 7248952059

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
TARGET   := library
OBJS     := main.o Book.o Library.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Library.h LibraryExceptions.h Book.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Book.o: Book.cpp Book.h LibraryExceptions.h
	$(CXX) $(CXXFLAGS) -c Book.cpp

Library.o: Library.cpp Library.h LibraryExceptions.h Book.h
	$(CXX) $(CXXFLAGS) -c Library.cpp

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all run clean

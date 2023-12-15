.PHONY: build clean run git all

CXX := g++
CXXFLAGS := -I src/include -L src/lib -I src/Graphics
LIBS := -lmingw32 -lSDL2main -lSDL2

build: program
	@echo ---BUILDING PROGRAM---

program: obj/main.o obj/color.o obj/ScreenBuffer.o
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

obj/ScreenBuffer.o: src/Graphics/ScreenBuffer.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $^

obj/color.o: src/Graphics/color.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $^


obj/main.o: main.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $^

all: build run clean

clean: 
	@echo ---Cleaning .o and .exe files---
	@del /Q obj\*.o
	@del /Q *.exe

run:
	@echo ---RUNNING PROGRAM---
	@./program
	@echo ---PROGRAM TERMINATED---

git:
	git add *
	git commit
	git push
	
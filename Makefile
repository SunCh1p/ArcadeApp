.PHONY: build clean run git all

CXX := g++
CXXFLAGS := -I src/include -L src/lib -I src/Graphics -I src/utils -I src/Shapes
LIBS := -lmingw32 -lSDL2main -lSDL2

build: program
	@echo ---BUILDING PROGRAM---

#linking files for main program
program: obj/main.o obj/Utils.o obj/Vec2D.o obj/Line2D.o obj/color.o obj/ScreenBuffer.o obj/Screen.o
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

#creating object files

obj/Line2D.o: src/Shapes/Line2D.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $^

obj/Utils.o: src/utils/Utils.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $^

obj/Vec2D.o: src/utils/Vec2D.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $^

obj/Screen.o: src/Graphics/screen.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $^

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
	
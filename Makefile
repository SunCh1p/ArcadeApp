.PHONY: build clean run git all
CXX := g++
CXXFLAGS := -I src/SDL2/include -L src/SDL2/lib -I src/Graphics -I src/utils -I src/Shapes
LIBS := -lmingw32 -lSDL2main -lSDL2

SRCDIRS:= . src src/Graphics src/utils src/Shapes
SRC:= $(wildcard *.cpp $(addsuffix /*.cpp, $(SRCDIRS)))
OBJ:= $(patsubst %.cpp, obj/%.o, $(notdir $(SRC)))


all: build run clean

build: program
	@echo ---Program Compiled: type './$(<)' or 'make run' to run---

run:
	@echo ---RUNNING PROGRAM---
	@./program
	@echo ---PROGRAM TERMINATED---

program: $(OBJ)
	@echo "Linking $^"
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

obj/%.o: %.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o: src/%.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o: src/Graphics/%.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o: src/utils/%.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/%.o: src/Shapes/%.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

clean: 
	@echo ---Cleaning .o and .exe files---
	@del /Q obj\*.o
	@del /Q *.exe

git:
	git add *
	git commit
	git push
	
.PHONY: build clean run git

CXX := g++
CXXFLAGS := -I src/include -L src/lib
LIBS := -lmingw32 -lSDL2main -lSDL2

build: program
	@echo "entering main"

program: obj/main.o
	@echo "linking"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

obj/main.o: main.cpp
	@echo "creating object files..."
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean: 
	del /Q obj\*.o
	del /Q *.exe

run:
	./program

git:
	
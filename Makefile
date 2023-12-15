.PHONY: build clean run git

CXX := g++
CXXFLAGS := -I src/include -L src/lib -I src/Graphics
LIBS := -lmingw32 -lSDL2main -lSDL2

build: program
	@echo "entering main"

program: obj/main.o obj/color.o obj/ScreenBuffer.o
	@echo "linking"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

obj/ScreenBuffer.o: src/Graphics/ScreenBuffer.cpp
	@echo "Creating color object file"
	$(CXX) $(CXXFLAGS) -c -o $@ $^

obj/color.o: src/Graphics/color.cpp
	@echo "Creating color object file"
	$(CXX) $(CXXFLAGS) -c -o $@ $^


obj/main.o: main.cpp
	@echo "creating object files..."
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean: 
	del /Q obj\*.o
	del /Q *.exe

run:
	./program

git:
	git add *
	git commit
	git push
	
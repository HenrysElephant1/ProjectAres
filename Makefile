EXE=Ares

all: $(EXE)


#  MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall
LIBS=-lglut32cu -lglu32 -lopengl32 -lSDL2
CLEAN=del *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations
LIBS=-framework GLUT -framework OpenGL -F /Library/Frameworks -framework SDL2
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm -lSDL2
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif


Main.o: Main.cpp
GameManager.o: GameManager.cpp GameManager.h
GLManager.o: GLManager.cpp GLManager.h stb_image.h
State.o: State.cpp State.h
ActiveGame.o: ActiveGame.cpp ActiveGame.h
MenuState.o: MenuState.cpp MenuState.h
MainMenu.o: MainMenu.cpp MainMenu.h
MapMenu.o: MapMenu.cpp MapMenu.h
PlayerMenu.o: PlayerMenu.cpp PlayerMenu.h
PauseMenu.o: PauseMenu.cpp PauseMenu.h
Button.o: Button.cpp Button.h


.c.o:
	gcc -c $(CFLG) $<
.cpp.o:
	g++ -std=c++11 -c $(CFLG) $<


Ares: Main.o GameManager.o GLManager.o State.o ActiveGame.o MenuState.o MainMenu.o MapMenu.o PlayerMenu.o PauseMenu.o Button.o
	g++ -O3 -o $@ $^ $(LIBS)

clean:
	$(CLEAN)
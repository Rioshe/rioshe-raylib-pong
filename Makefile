CC = gcc
CFLAGS = -Ilibs/include
SRC = src/main.c src/game.c src/ball.c src/paddles.c src/collision.c src/score.c
OUT = build/game.exe
LIBS = libs/libraylib.a -lopengl32 -lgdi32 -lwinmm

run:
	@echo Cleaning...
	@rm -f $(OUT)
	@mkdir -p build
	@echo Compiling...
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)
	@echo Running...
	./$(OUT)
	@echo Done!
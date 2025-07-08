CC = gcc
CFLAGS ?= -Ilibs/include
SRC ?= src/main.c src/game.c src/ball.c src/paddles.c src/collision.c src/score.c src/sound.c
OUT ?= build/game.exe
LIBS ?= -L./libs -l:libraylib.a

# Set platform-specific libraries
ifeq ($(OS),Windows_NT)
	LIBS += -lopengl32 -lgdi32 -lwinmm
else
	LIBS += -lm
endif

run: $(OUT)
	@echo Running...
	./$(OUT)
	@echo Done!

$(OUT): $(SRC) build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

build:
	mkdir -p build

clean:
	rm -f $(OUT)

.PHONY: clean run play build
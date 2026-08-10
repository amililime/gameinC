# Requires raylib: brew install raylib
CC      = clang
CFLAGS  = -Wall -Wextra -std=c99 -O2 -Isrc
TARGET  = tetris
SRC     = $(wildcard src/*.c)

RAYLIB  := $(shell pkg-config --cflags --libs raylib 2>/dev/null)
ifeq ($(RAYLIB),)
RAYLIB  = -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib \
          -framework OpenGL -framework Cocoa -framework IOKit \
          -framework CoreVideo -framework CoreAudio
endif

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ $(RAYLIB) -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean

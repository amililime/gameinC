# Requires raylib: brew install raylib
CC      = clang
CFLAGS  = -Wall -Wextra -std=c99 -O2 -Isrc
TARGET  = tetris
SRC     = $(wildcard src/*.c)
APP     = Tetris.app

RAYLIB_INC = /opt/homebrew/include
RAYLIB_LIB = /opt/homebrew/lib

# Dynamic link (for local dev)
RAYLIB  := $(shell pkg-config --cflags --libs raylib 2>/dev/null)
ifeq ($(RAYLIB),)
RAYLIB  = -I$(RAYLIB_INC) -L$(RAYLIB_LIB) -lraylib \
          -framework OpenGL -framework Cocoa -framework IOKit \
          -framework CoreVideo -framework CoreAudio
endif

# Static link (for .app bundle — no raylib install needed on target machine)
RAYLIB_STATIC = -I$(RAYLIB_INC) $(RAYLIB_LIB)/libraylib.a \
                -framework OpenGL -framework Cocoa -framework IOKit \
                -framework CoreVideo -framework CoreAudio

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ $(RAYLIB) -o $@

run: all
	./$(TARGET)

app: $(SRC)
	$(CC) $(CFLAGS) $^ $(RAYLIB_STATIC) -o $(TARGET)
	mkdir -p $(APP)/Contents/MacOS
	mkdir -p $(APP)/Contents/Resources
	cp $(TARGET) $(APP)/Contents/MacOS/tetris
	cp res/Info.plist $(APP)/Contents/Info.plist
	@echo "Built $(APP) — right-click > Open on first launch if unsigned"

clean:
	rm -f $(TARGET)
	rm -rf $(APP)

.PHONY: all run app clean

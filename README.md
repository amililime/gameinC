# gameinC

The Tetris film inspired me to code this in C. I used [Raylib](https://www.raylib.com/) and kept it simple.

## Controls

| Key | Action |
|-----|--------|
| ← → | Move left / right |
| ↑ or X | Rotate clockwise |
| Z | Rotate counter-clockwise |
| ↓ | Soft drop |
| Space | Hard drop |
| P | Pause / unpause |
| Enter | Restart after game over |

## Running the game

### macOS

Requires [Homebrew](https://brew.sh/).

```sh
brew install raylib
make run
```

### Linux

Install raylib for your distro, then compile:

**Ubuntu / Debian**
```sh
sudo apt install libraylib-dev
gcc src/*.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o tetris
./tetris
```

**Arch**
```sh
sudo pacman -S raylib
gcc src/*.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o tetris
./tetris
```

### Windows

1. Download and install [raylib](https://www.raylib.com/) — the Windows installer bundles MinGW.
2. Open the raylib shell and compile:

```sh
gcc src/*.c -lraylib -lopengl32 -lgdi32 -lwinmm -o tetris.exe
tetris.exe
```

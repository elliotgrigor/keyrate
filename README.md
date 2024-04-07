# keyrate

Small utility for setting the keyrate to higher speeds than is normally allowed
by the Windows keyboard control panel.

## Installation

**Note**: Assumes the use of mingw64.

Produces substantially larger binaries compared to the original. (91KB vs 3KB)

`make build` or `gcc.exe -O2 -o keyrate.exe keyrate.c`

## Usage

`keyrate.exe <delay ms> <rate ms>`

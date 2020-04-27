[![Total alerts](https://img.shields.io/lgtm/alerts/g/wtlgo/brainfuck.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wtlgo/brainfuck/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/wtlgo/brainfuck.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/wtlgo/brainfuck/context:cpp)


# Brainfuck interpreter

 Yet Another Brainfuck Interpreter

## Requirements

- CMake >= 3.12
- C++14 compatible compiler
- git

## How to build

```bash
$ git clone https://github.com/wtlgo/brainfuck.git
$ mkdir brainfuck/build && cd brainfuck/build
$ cmake ..
$ cmake --build .
$ cmake --install .
```

## How to use

```bash
$ ./bf --help

Brainfuck interpreter by wtlgo
https://github.com/wtlgo/brainfuck.git

Flags:
    -s [filename]       Specify source file.
    -c [code]           Specify source via command line.

    -i [filename]       Input file. If not specified, stdin is used.
    -o [filename]       Output file. If not specified stdout is used.

    --infinite-tape     Make tape infinite. By default limited to 3000 cells.
    --wrapped-tape      Make tape wrapped. Not wrapped by default.

    --signed-cells      Make cells signed. Unsigned by default.
    --unwrapped-cells   Make cells unwrapped. Wrapped by default.

    --comments          Enable C-style comments. Disabled by default.

    --help              This page.
```

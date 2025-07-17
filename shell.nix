{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.gcc
    pkgs.cmake
    pkgs.pkg-config
    pkgs.ncurses # Provides both C and C++ (curses++) interfaces
  ];
  shellHook = ''
    echo "Development environment for C++ with ncurses (curses++) ready."
    echo "To use the C++ interface, include <cursesw.h> and link with -lncurses++."
  '';
} 
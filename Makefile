CXX = g++
IDIR = ./include
SDL2CFLAGS := $(shell sdl2-config --cflags)
SDL2LIBS := $(shell sdl2-config --libs)
CXXFLAGS = -Wall -pedantic -std=c++17 -I$(IDIR) $(SDL2CFLAGS) -g
ODIR = src/obj

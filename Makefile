CXX = g++
IDIR = ./include
BUILDDIR = ./build
SDL2CFLAGS := $(shell sdl2-config --cflags)
SDL2LIBS := -L./external/SDL -Wl,--enable-new-dtags -lSDL2
GLLIBS := -lglut
CXXFLAGS = -Wall -pedantic -std=c++17 -I$(IDIR) $(SDL2CFLAGS) -g
ODIR = src/obj

_DEPS = GameClass.h
DEPS = $(patsubst %, $(INCLUDE)/%, $(_DEPS))

_OBJ = main.o GameClass.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

$(ODIR)/%.o: src/%.cpp | $(ODIR)
	$(CXX) -c $< $(CXXFLAGS) -o $@

jail: $(OBJ) | $(ODIR)
	mkdir -p $(BUILDDIR)/
	$(CXX) -o $(BUILDDIR)/$@ $^ $(CXXFLAGS) $(GLLIBS) $(SDL2LIBS)

$(ODIR):
	@echo "Folder $(ODIR) does not exist. Creating"
	mkdir -p $@

$(BUILDDIR):
	@echo "Folder $(BUILDDIR) does not exist. Creating"
	mkdir -p $@

.PHONY: clean all

clean:
	-rm $(ODIR)/*.o
	-rm -r $(BUILDDIR)/


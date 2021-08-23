IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR) `sdl2-config --cflags --libs` -lSDL2_image

ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = wall.h SDL_helpers.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = wortec.o wall.o SDL_helpers.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

#$(info $$OBJ/%.o is [${OBJ}])

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

wortec: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

CC = cc68x

RAST_OBJS = bitmaps.o raster.o tst_rast.o
RAST = tst_rast

MOD_OBJS = events.o model.o input.o tst_mod.o
MOD = tst_mod

REN_OBJS = events.o model.o render.o bitmaps.o raster.o input.o tst_ren.o
REN = tst_ren

ESC_OBJ = model.o events.o render.o raster.o bitmaps.o input.o dino_esc.o
ESC = dino_esc

all: raster model render game

raster: $(RAST)
model: $(MOD)
render: $(REN)
game: $(ESC)

$(RAST): $(RAST_OBJS)
	$(CC) -o $(RAST) $(RAST_OBJS)

$(MOD): $(MOD_OBJS)
	$(CC) -o $(MOD) $(MOD_OBJS)

$(REN): $(REN_OBJS)
	$(CC) -o $(REN) $(REN_OBJS)

$(ESC): $(ESC_OBJ)
	$(CC) -o $(ESC) $(ESC_OBJ)

render.o: render.c render.h
	$(CC) -c render.c

events.o: events.c events.h
	$(CC) -c events.c

model.o: model.c model.h
	$(CC) -c model.c

bitmaps.o: bitmaps.c bitmaps.h
	$(CC) -c bitmaps.c

raster.o: raster.c raster.h
	$(CC) -c raster.c

input.o: input.c input.h
	$(CC) -c input.c

tst_rast.o: tst_rast.c raster.h
	$(CC) -c tst_rast.c

tst_ren.o: tst_ren.c render.h events.h model.h
	$(CC) -c tst_ren.c

tst_mod.o: tst_mod.c tst_mod.h model.h
	$(CC) -c tst_mod.c

dino_esc.o: dino_esc.c
	$(CC) -c dino_esc.c

clean: clean_model clean_raster clean_render clean_game

clean_model:
	$(RM) $(MOD_OBJS) $(MOD)

clean_raster:
	$(RM) $(RAST_OBJS) $(RAST)

clean_render:
	$(RM) $(REN_OBJS) $(REN)

clean_game:
	$(RM) $(ESC_OBJ) $(ESC)

CC = cc68x

RAST_OBJS = bitmaps.o raster.o tst_rast.o
RAST = tst_rast

MOD_OBJS = events.o model.o input.o tst_mod.o
MOD = tst_mod

REN_OBJS = events.o model.o render.o bitmaps.o raster.o input.o tst_ren.o
REN = tst_ren

ESC_OBJ = model.o events.o render.o raster.o bitmaps.o input.o clock.o dino_esc.o
ESC = dino_esc

SND_OBJS = tst_snd.o game_sound.o
SND = tst_snd

all: raster model render game sound

raster: $(RAST)
model: $(MOD)
render: $(REN)
game: $(ESC)
sound: $(SND)

$(RAST): $(RAST_OBJS)
	$(CC) -o $(RAST) $(RAST_OBJS)

$(MOD): $(MOD_OBJS)
	$(CC) -o $(MOD) $(MOD_OBJS)

$(REN): $(REN_OBJS)
	$(CC) -o $(REN) $(REN_OBJS)

$(ESC): $(ESC_OBJ)
	$(CC) -o $(ESC) $(ESC_OBJ)

$(SND): $(SND_OBJS)
	$(CC) -o $(SND) $(SND_OBJS)

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

clock.o: clock.c clock.h
	$(CC) -c clock.c

game_sound.o: game_snd.c game_snd.h
	$(CC) game_snd.c

tst_rast.o: tst_rast.c raster.h
	$(CC) -c tst_rast.c

tst_ren.o: tst_ren.c render.h events.h model.h
	$(CC) -c tst_ren.c

tst_mod.o: tst_mod.c tst_mod.h model.h
	$(CC) -c tst_mod.c

dino_esc.o: dino_esc.c
	$(CC) -c dino_esc.c

tst_snd.o: tst_snd.c
	$(CC) tst_snd.c

clean: clean_model clean_raster clean_render clean_game clean_sound

clean_model:
	$(RM) $(MOD_OBJS) $(MOD)

clean_raster:
	$(RM) $(RAST_OBJS) $(RAST)

clean_render:
	$(RM) $(REN_OBJS) $(REN)

clean_game:
	$(RM) $(ESC_OBJ) $(ESC)

clean_sound:
	$(RM) $(SND_OBJS) $(SND)

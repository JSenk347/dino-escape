CC = cc68x

RAST_OBJS = bitmaps.o raster.o tst_rast.o
RAST = tst_rast

MOD_OBJS = events.o model.o input.o tst_mod.o
MOD = tst_mod

REN_OBJS = events.o model.o render.o bitmaps.o raster.o input.o tst_ren.o
REN = tst_ren

ESC_OBJ = model.o events.o render.o raster.o bitmaps.o input.o clock.o effects.o music.o psg.o dino_esc.o
ESC = dino_esc

EFF_OBJS = tst_eff.o psg.o effects.o
EFF = tst_eff

MUS_OBJS = tst_mus.o music.o psg.o clock.o
MUS = tst_mus

PSG_OBJS = tst_psg.o psg.o
PSG = tst_psg

all: raster model render game effects music psg

raster: $(RAST)
model: $(MOD)
render: $(REN)
game: $(ESC)
effects: $(EFF)
music: $(MUS)
psg: $(PSG)

$(RAST): $(RAST_OBJS)
	$(CC) -o $(RAST) $(RAST_OBJS)

$(MOD): $(MOD_OBJS)
	$(CC) -o $(MOD) $(MOD_OBJS)

$(REN): $(REN_OBJS)
	$(CC) -o $(REN) $(REN_OBJS)

$(ESC): $(ESC_OBJ)
	$(CC) -o $(ESC) $(ESC_OBJ)

$(EFF): $(EFF_OBJS)
	$(CC) -o $(EFF) $(EFF_OBJS)

$(MUS): $(MUS_OBJS)
	$(CC) -o $(MUS) $(MUS_OBJS)

$(PSG): $(PSG_OBJS)
	$(CC) -o $(PSG) $(PSG_OBJS)

render.o: render.c render.h
	$(CC) -c render.c

events.o: events.c effects.o events.h
	$(CC) -c events.c

model.o: model.c model.h
	$(CC) -c model.c

bitmaps.o: bitmaps.c bitmaps.h
	$(CC) -c bitmaps.c

raster.o: raster.c raster.h types.h
	$(CC) -c raster.c

input.o: input.c input.h
	$(CC) -c input.c

clock.o: clock.c clock.h
	$(CC) -c clock.c

effects.o: effects.c psg.h effects.h
	$(CC) -c effects.c

music.o: music.c psg.h clock.h
	$(CC) -c music.c

psg.o: psg.c psg.h
	$(CC) -c psg.c

tst_rast.o: tst_rast.c raster.h
	$(CC) -c tst_rast.c

tst_ren.o: tst_ren.c render.h events.h model.h
	$(CC) -c tst_ren.c

tst_mod.o: tst_mod.c tst_mod.h model.h
	$(CC) -c tst_mod.c

dino_esc.o: dino_esc.c
	$(CC) -c dino_esc.c

tst_eff.o: tst_eff.c effects.h
	$(CC) -c tst_eff.c

tst_mus.o: tst_mus.c music.h psg.h
	$(CC) -c tst_mus.c

tst_psg.o: tst_psg.c psg.h
	$(CC) -c tst_psg.c

clean: clean_model clean_raster clean_render clean_game clean_effects clean_music clean_psg

clean_model:
	$(RM) $(MOD_OBJS) $(MOD)

clean_raster:
	$(RM) $(RAST_OBJS) $(RAST)

clean_render:
	$(RM) $(REN_OBJS) $(REN)

clean_game:
	$(RM) $(ESC_OBJ) $(ESC)

clean_effects:
	$(RM) $(EFF_OBJS) $(EFF)

clean_music:
	$(RM) $(MUS_OBJS) $(MUS)

clean_psg:
	$(RM) $(PSG_OBJS) $(PSG)

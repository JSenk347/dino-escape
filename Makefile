CC = cc68x

RAST_OBJS = bitmaps.o raster.o tst_rast.o
RAST = tst_rast

MOD_OBJS = events.o model.o tst_mod.o
MOD = tst_mod

REN_OBJS = events.o model.o render.o bitmaps.o raster.o tst_ren.o
REN = tst_ren

all: raster model render

raster: $(RAST)
model: $(MOD)
render: $(REN)

$(RAST): $(RAST_OBJS)
	$(CC) -o $(RAST) $(RAST_OBJS)

$(MOD): $(MOD_OBJS)
	$(CC) -o $(MOD) $(MOD_OBJS)

$(REN): $(REN_OBJS)
	$(CC) -o $(REN) $(REN_OBJS)	

render.o: render.c render.h
	$(CC) -c render.c

events.o: events.c events.h
	$(CC) -c events.c

model.o: model.c model.h
	$(CC) -c model.c

bitmaps.o: bitmaps.c bitmaps.h raster.h
	$(CC) -c bitmaps.c

raster.o: raster.c raster.h
	$(CC) -c raster.c

tst_rast.o: tst_rast.c raster.h
	$(CC) -c tst_rast.c

tst_ren.o: tst_ren.c tst_mod.h render.h events.h model.h
	$(CC) -c tst_ren.c

tst_mod.o: tst_mod.c tst_mod.h model.h
	$(CC) -c tst_mod.c

clean: clean_model clean_raster clean_render

clean_model:
	$(RM) $(MOD_OBJS) $(MOD)

clean_raster:
	$(RM) $(RAST_OBJS) $(RAST)

clean_render:
	$(RM) $(REN_OBJS) $(REN)

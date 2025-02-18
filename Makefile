CC = cc68x

RAST_OBJS = bitmaps.o raster.o tst_rast.o
RAST = tst_rast

MOD_OBJS = events.o model.o tst_mod.o
MOD = tst_mod

raster: $(RAST)

model: $(MOD)

$(RAST): $(RAST_OBJS)
	$(CC) -o $(RAST) $(RAST_OBJS)

$(MOD): $(MOD_OBJS)
	$(CC) -o $(MOD) $(MOD_OBJS)

events.o: events.c events.h
	$(CC) -c events.c

model.o: model.c model.h
	$(CC) -c model.c

tst_model: tst_mod.c tst_mod.h
	$(CC) -c tst_mod.c

bitmaps.o: bitmaps.c bitmaps.h raster.h
	$(CC) -c bitmaps.c

raster.o: raster.c raster.h
	$(CC) -c raster.c

tst_rast.o: tst_rast.c raster.h
	$(CC) -c tst_rast.c

clean_model:
	$(RM) $(MOD_OBJS) $(MOD)

clean_raster:
	$(RM) $(RAST_OBJS) $(RAST)







	
CC = cc68x

OBJ = bitmaps.o raster.o tst_rast.o
EXEC = tst_rast

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

bitmaps.o: bitmaps.c bitmaps.h raster.h
	$(CC) -c bitmaps.c

raster.o: raster.c raster.h
	$(CC) -c raster.c

tst_rast.o: tst_rast.c raster.h
	$(CC) -c tst_rast.c -o tst_rast.o

clean:
	$(RM) *.o
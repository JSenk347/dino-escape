tst_rast: tst_rast.o raster.o rast_asm.o
    cc68x -g tst_rast.o raster.o rast_asm.o -o tst_rast

tst_rast.o: tst_rast.c raster.h
    cc68x -g -c tst_rast.c

raster.o: raster.c raster.h
    cc68x -g -c raster.c

rast_asm.o: rast_asm.s
    gen -D -L2 rast_asm.s
tst_rast: tst_rast.o raster.o rast_asm.o bitmaps.o
    cc68x -g tst_rast.o raster.o rast_asm.o bitmaps.o -o tst_rast

tst_rast.o: tst_rast.c raster.h
    cc68x -g -c tst_rast.c

raster.o: raster.c raster.h
    cc68x -g -c raster.c

rast_asm.o: rast_asm.s
    gen -D -L2 rast_asm.s

bitmaps.o: bitmaps.c raster.h
    cc68x -g -c bitmaps.c

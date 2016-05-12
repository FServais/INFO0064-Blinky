 CFLAGS = --std=c99 --pedantic -Wall -Wextra -Wmissing-prototypes
LDFLAGS = -lm

track_test: test_track.o track.o
	gcc test_track.o track.o -o track_test $(LDFLAGS)

test_track.o: test_track.c
	gcc $(CFLAGS) -c test_track.c -o test_track.o

track.o: track.c track.h
	gcc $(CFLAGS) -c track.c -o track.o

clean:
	rm -f *~ *.o track_test


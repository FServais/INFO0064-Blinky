 CFLAGS = --std=c99 --pedantic -Wall -Wextra -Wmissing-prototypes
LDFLAGS = -lm

track_test: test_track.o track.o sim.o
	gcc test_track.o track.o sim.o -o track_test $(LDFLAGS)

test_track.o: test_track.c
	gcc $(CFLAGS) -c test_track.c -o test_track.o

sim.o: simulation.c simulation.h
	gcc $(CFLAGS) -c simulation.c -o sim.o

track.o: track.c track.h
	gcc $(CFLAGS) -c track.c -o track.o

clean:
	rm -f *~ *.o track_test


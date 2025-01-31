CC := gcc
CFLAGS := -O0 -g3

.PHONY: clean
clean:
	rm -f *.o taco

.DEFAULT_GOAL := taco

OBJ = main.o saus.o lefse.o krydder.o protein.o grønnsaker.o drikke.o

taco: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.
	$(CC) $(CFLAGS) -c main.c -o main.o

saus.o: taco_saus.c
	$(CC) $(CFLAGS) -c taco_saus.c -o saus.o

lefse.o: taco_lefse.c
	$(CC) $(CFLAGS) -c taco_lefse.c -o lefse.o

krydder.o: taco_krydder.c
	$(CC) $(CFLAGS) -c taco_krydder.c -o krydder.o

protein.o: protein.c
	$(CC) $(CFLAGS) -c protein.c -o protein.o

gronnsaker.o: grønnsaker.c
	$(CC) $(CFLAGS) -c gronnsaker.c -o gronnsaker.o

drikke.o: drikke.c
	$(CC) $(CFLAGS) -c drikke.c -o drikke.o


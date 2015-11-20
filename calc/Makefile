CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -g
OBJECTS = calc.c return.c result.c
EXES = calc

calc:	$(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS)

%.o:	%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXES)

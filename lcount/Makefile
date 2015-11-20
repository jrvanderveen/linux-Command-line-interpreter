CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -g
OBJECTS = lcount.c count.c
EXES = lcount

lcount:	$(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS)

%.o:	%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXES)

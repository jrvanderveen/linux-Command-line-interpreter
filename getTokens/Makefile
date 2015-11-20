CC = gcc
CFLAGS = -Wall -g 
LDFLAGS = -g
OBJECTS = tokenizer.o
EXES = tokentest

tokentest:	$(OBJECTS)
	$(CC) -o $@ $(LDFLAGS) $(OBJECTS)

%.o:	%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXES)

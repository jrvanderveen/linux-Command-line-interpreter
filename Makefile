CC = gcc
CFLAGS = -Wall -c
LDFLAGS = -g
CALCOBJ = calc/calc.c calc/result.c calc/return.c
LCOUNTOBJ = lcount/count.c lcount/lcount.c
CLIOBJECTS = cli.o getTokens/tokenizer.o utils/utils.o inputMode/ttymode.o dLL/dll.o
EXES = cli lcount/lcount calc/calc

all:	$(EXES)

lcount/lcount:	$(LCOUNTOBJ)
	$(CC) -o $@ $(LDFLAGS) $(LCOUNTOBJ)
lcount/%.o:	lcount/%.c
	$(CC) -c $(CFLAGS) $< -o $@

calc/calc:	$(CALCOBJ)
	$(CC) -o $@ $(LDFLAGS) $(CALCOBJ)
calc/%.o:	calc/%.c
	$(CC) -c $(CFLAGS) $< -o $@
	
cli:	$(CLIOBJECTS)
	$(CC) -o $@ $(LDFLAGS) $(CLIOBJECTS)
%.o:	%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXES)

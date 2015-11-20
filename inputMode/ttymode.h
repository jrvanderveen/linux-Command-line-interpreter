/*
 *	ttymode.h
 *
 *	adapted from APUE 18.20
 *
 *	set, unset cbreak mode for input
 *
 *	D Bover, WWU Computer Science, April 2008
 *
 */

#ifndef TTYMODE
#define TTYMODE

int tty_cbreak(int fd);	/* put terminal into a cbreak mode */

int tty_reset(int fd); 	/* restore terminal to cooked mode */

void tty_atexit(void);	/* can be set up by atexit(tty_atexit) */
	
#endif

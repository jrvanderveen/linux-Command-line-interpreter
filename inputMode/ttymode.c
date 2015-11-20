/*
 *	ttymode.c
 *
 *	adapted from APUE 18.20
 *
 *	set, unset cbreak mode for input
 *
 *	D Bover, WWU Computer Science, April 2008
 *
 */

#include	<termios.h>
#include	<unistd.h>

static struct termios	save_termios;
static int	  ttysavefd = -1;
static enum { RESET, CBREAK }	ttystate = RESET;

int tty_cbreak(int fd)	/* put terminal into a cbreak mode */
{
	struct termios	buf;

	if (tcgetattr(fd, &save_termios) < 0)
		return(-1);

	buf = save_termios;	/* structure copy */

	buf.c_lflag &= ~(ECHO | ICANON);
					/* echo off, canonical mode off */

	buf.c_cc[VMIN] = 1;	 /* 1 byte at a time, no timer */
	buf.c_cc[VTIME] = 0;

	if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
		return(-1);
	ttystate = CBREAK;
	ttysavefd = fd;
	return(0);
}


int tty_reset(int fd)		/* restore terminal's mode */
{
	if (ttystate != CBREAK)
		return(0);

	if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
		return(-1);
	ttystate = RESET;
	return(0);
}

void tty_atexit(void)		/* can be set up by atexit(tty_atexit) */
{
	if (ttysavefd >= 0)
		tty_reset(ttysavefd);
}



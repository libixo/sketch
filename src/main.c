#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <signal.h>

#include <valgrind/valgrind.h>


#include "module.h"
#include "window.h"

/* _m and _w are globals used for editing, _m_rt is the thread-safe module */
Window *_w;
Module *_m;
Module *_m_rt;

void cleanup(void);

#include "event.h"
#include "ui/ui.h"

#define FRAMETIME 20 * 1000000 /* multiplied by 1 million to get milliseconds */

/* never returns */
void cleanup(void)
{
	VALGRIND_PRINTF("cleanup\n");
	freeModule(_m);
	freeWindow(_w);
	freeTerminal();

	sigaction(SIGINT, &(struct sigaction){.sa_handler = SIG_DFL}, NULL); /* avoid locking up sigint */

	exit(0);
}

static void _quitHandler(int signal)
{
	VALGRIND_PRINTF("_quitHandler\n");
	pushEvent(QUEUE_MAIN, (Event){EVENT_QUIT, NULL});
}

int main(int argc, char *argv[])
{
	struct timespec req;

	/* set signals */
	sigaction(SIGINT, &(struct sigaction){.sa_handler = _quitHandler}, NULL);

	allocTerminal();

	_m = allocModule();
	_w = allocWindow();

	/* initialize the screen */
	_w->redraw = 1;

	while (true)
	{
		input();
		procEvents(QUEUE_MAIN);

		/* delay till the next event poll */
		req.tv_sec = 0;
		req.tv_nsec = FRAMETIME;
		nanosleep(&req, NULL);
	}

	return 0;
}

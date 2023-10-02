#ifndef TRACKER_UI_UI_C
#define TRACKER_UI_UI_C

#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>

Rect _windowSize;

static void _winchHandler(int signal)
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	_windowSize.x = 0;
	_windowSize.y = 0;
	_windowSize.w = w.ws_col;
	_windowSize.h = w.ws_row;
	pushEvent(QUEUE_MAIN, (Event){EVENT_REDRAW, NULL});
}

void allocTerminal(void)
{
	/* disable canonical echo */
	struct termios tc;
	tcgetattr(0, &tc);
	tc.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &tc);

	/* set signals */
	signal(SIGWINCH, _winchHandler);

	puts("\033[?1049h"); /* set the alt screen buffer */
}

void freeTerminal(void)
{
	puts("\033[?1049l"); /* unset the alt screen buffer */

	/* enable canonical echo */
	struct termios tc;
	tcgetattr(0, &tc);
	tc.c_lflag &= (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &tc);
}

static void _drawPage(void)
{
	printf("\033[1;1H");

	for (int i = 0; i < PAGE_COUNT; i++)
	{
		if (_w->page == i) printf("\033[1m"); /* bold */

		printf("%s ", PageNames[i]);
		printf("\033[22m"); /* reset intensity */
	}
}

void draw(void)
{
	puts("\033[2J"); /* clear screen */

	_drawPage();

	/* explicitly dump stdin */
	printf("\n");
	fflush(stdin);
}

/* returns true if input was handled */
int _uiInput(int input)
{
	switch (input)
	{
		case MOD_CTRL + 'X': /* quit   */ pushEvent(QUEUE_MAIN, (Event){EVENT_QUIT,   NULL}); return 1;
		case MOD_CTRL + 'L': /* redraw */ pushEvent(QUEUE_MAIN, (Event){EVENT_REDRAW, NULL}); return 1;
		case '\033':
			switch (input = getchar())
			{
				case '[': switch (input = getchar())
				{
					case 'O': switch (input = getchar())
					{
						case 'P': /* F1 */ _w->page = 0; pushEvent(QUEUE_MAIN, (Event){EVENT_REDRAW, NULL}); break;
						case 'Q': /* F2 */ _w->page = 1; pushEvent(QUEUE_MAIN, (Event){EVENT_REDRAW, NULL}); break;
						case 'R': /* F3 */ _w->page = 2; pushEvent(QUEUE_MAIN, (Event){EVENT_REDRAW, NULL}); break;
						case 'S': /* F4 */ _w->page = 3; pushEvent(QUEUE_MAIN, (Event){EVENT_REDRAW, NULL}); break;
					} break;
				} break;
			} return 1;
	}
	return 0;
}

void input(void)
{
	int status = fcntl(0, F_GETFL);
	fcntl(0, F_SETFL, status | O_NONBLOCK); /* set stdin to nonblocking */

	int input;
	while ((input = getchar()) != EOF)
	{
		_uiInput(input);
	}
	fcntl(0, F_SETFL, status); /* reset the old file descriptor flags */
}

#endif /* TRACKER_UI_UI_C */

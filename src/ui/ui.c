#ifndef TRACKER_UI_UI_C
#define TRACKER_UI_UI_C

#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>

Rect _windowSize;

static void _winchHandler(int signal)
{
	VALGRIND_PRINTF("_winchHandler\n");
	struct winsize winsz;
	ioctl(0, TIOCGWINSZ, &winsz);
	_windowSize.x = 0;
	_windowSize.y = 0;
	_windowSize.w = winsz.ws_col;
	_windowSize.h = winsz.ws_row;
	_w->redraw = 1;
}

void allocTerminal(void)
{
	/* disable canonical echo */
	struct termios tc;
	tcgetattr(0, &tc);
	tc.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0, TCSANOW, &tc);

	/* set signals */
	sigaction(SIGINT, &(struct sigaction){.sa_handler = _winchHandler}, NULL);

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

	switch (_w->page)
	{
		case PAGE_GENERAL: drawGeneral(); break;
	}

	/* explicitly dump stdin */
	printf("\n");
	fflush(stdin);
}

/* returns true if input was handled */
int _inputUI(int input)
{
	switch (input)
	{
		case MOD_CTRL + 'X': /* quit   */ pushEvent(QUEUE_MAIN, (Event){EVENT_QUIT, NULL}); return 1;
		case MOD_CTRL + 'L': /* redraw */ _w->redraw = 1; return 1;
		case '\033':
			switch (input = getchar()) {
				case 'O': switch (input = getchar()) { /* SS3 */
					case 'P': /* F1 */ _w->page = 0; _w->redraw = 1; break;
					case 'Q': /* F2 */ _w->page = 1; _w->redraw = 1; break;
					case 'R': /* F3 */ _w->page = 2; _w->redraw = 1; break;
					case 'S': /* F4 */ _w->page = 3; _w->redraw = 1; break;
				} break;
				case '[': switch (input = getchar()) { /* CSI */
				} break;
			} return 1;
		default: return 0;
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
		if (_inputUI(input)) break;
		if (inputGeneral(input)) break;
	}
	fcntl(0, F_SETFL, status); /* reset the old file descriptor flags */
}

#endif /* TRACKER_UI_UI_C */

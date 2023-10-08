void drawGeneral(void)
{
	printf("\033[%d;%dH", _w->cursor.y, _w->cursor.x);
}

int inputGeneral(int input)
{
	switch (input)
	{
		case '\033':
			switch (input = getchar()) {
				case '[': switch (input = getchar()) { /* CSI */
					case 'A': /* Up    */ _w->cursor.y--; _w->redraw = 1; break;
					case 'B': /* Down  */ _w->cursor.y++; _w->redraw = 1; break;
					case 'D': /* Left  */ _w->cursor.x--; _w->redraw = 1; break;
					case 'C': /* Right */ _w->cursor.x++; _w->redraw = 1; break;
				} break;
			} return 1;
		default: return 0;
	} return 0;
}

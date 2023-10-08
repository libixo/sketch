#ifndef TRACKER_WINDOW_H
#define TRACKER_WINDOW_H

typedef enum Page
{
	PAGE_GENERAL = 0,  /* f1 */
	PAGE_PATTERN,      /* f2 */
	PAGE_SAMPLE,       /* f3 */
	PAGE_INSTRUMENT,   /* f4 */
	PAGE_COUNT
} Page;

char *PageNames[PAGE_COUNT] =
{
	[PAGE_GENERAL]    = "GENERAL",
	[PAGE_PATTERN]    = "PATTERN",
	[PAGE_SAMPLE]     = "SAMPLE",
	[PAGE_INSTRUMENT] = "INSTRUMENT",
};

typedef struct Pos
{
	int x;
	int y;
} Pos;


typedef struct Window
{
	Page page;

	Pos cursor;

	InstrumentIndex instrument;

	int redraw; /* set high to request a redraw */
} Window;

Window *allocWindow(void);
void freeWindow(Window*);

#include "window.c"
#endif /* TRACKER_WINDOW_H */

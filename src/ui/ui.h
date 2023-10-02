#ifndef TRACKER_UI_UI_H
#define TRACKER_UI_UI_H

#define MOD_SHIFT -0x20
#define MOD_CTRL  -0x40

#include "control.h"
#include "general.h"

void draw(void);
void input(void);
void allocTerminal(void);
void freeTerminal(void);

typedef struct Rect
{
	int x;
	int y;
	int w;
	int h;
} Rect;

Rect *getWindowSize(void);

#include "ui.c"
#endif /* TRACKER_UI_UI_H */

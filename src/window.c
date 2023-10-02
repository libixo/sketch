#ifndef TRACKER_WINDOW_C
#define TRACKER_WINDOW_C

Window *allocWindow(void)
{
	Window *new = calloc(1, sizeof(Window));

	return new;
}

void freeWindow(Window *w)
{
	free(w);
}

#endif /* TRACKER_WINDOW_C */

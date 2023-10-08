#ifndef TRACKER_EVENT_C
#define TRACKER_EVENT_C

#include "ui/ui.h"

typedef struct Queue
{
	int pos;
	Event event[EVENT_QUEUE_LEN];
} Queue;

Queue _eventQueue[EVENT_QUEUE_COUNT] = {0};

void procEvents(int queue)
{
	Event *e;
	Queue *q = &_eventQueue[queue];
	while (q->pos)
	{
		e = &q->event[--(q->pos)];
		VALGRIND_PRINTF("handling event %d\n", e->code);
		switch (e->code)
		{
			case EVENT_NULL:
				break;
			case EVENT_QUIT:
				cleanup();
				break;
		}
	}

	if (_w->redraw)
	{
		_w->redraw = 0;
		VALGRIND_PRINTF("handling redraw\n");
		draw();
	}
}

void pushEvent(int queue, Event e)
{
	Queue *q = &_eventQueue[queue];

	q->event[(q->pos)++] = e;
}

#endif /* TRACKER_EVENT_C */

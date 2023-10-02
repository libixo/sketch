#ifndef TRACKER_EVENT_H
#define TRACKER_EVENT_H

#define EVENT_QUEUE_LEN 32
#define EVENT_QUEUE_COUNT 2

/* queue names */
#define QUEUE_MAIN 0
#define QUEUE_RT   1

typedef enum EventCode
{
	EVENT_NULL,
	EVENT_REDRAW,
	EVENT_QUIT,
} EventCode;

typedef struct Event
{
	enum EventCode code;
	void          *arg;
} Event;

void pushEvent(int queue, Event e); /* push event .e to queue .queue     */
void procEvents(int queue);         /* handle all events in queue .queue */

#include "event.c"
#endif /* TRACKER_EVENT_H */

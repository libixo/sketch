#ifndef TRACKER_CHANNEL_H
#define TRACKER_CHANNEL_H

/* channel definition */
struct _Channel;

#include "pattern.h"

#define CHANNEL_COUNT 256
typedef uint8_t ChannelIndex;

/* channels are linked lists */
typedef struct _Channel
{
	char    name[NAME_LEN+1];
	uint8_t volume;
	int8_t  panning;

	bool mute;     /* disable channel audio output, still process fully internally */
	bool surround; /* pro logic surround (invert the phase of the right speaker) */

	uint8_t effect; /* where in the effect chain to output to, EFFECT_VOID to output straight to the speakers */
	uint8_t effectmix;

	Pattern *pattern[PATTERN_MAX];

	struct _Channel *prev; /* previous channel, or NULL if this is the first channel */
	struct _Channel *next; /* next channel, or NULL if this is the last channel      */
} Channel;

Channel *addChannelAfter (struct _Module*, Channel*);
Channel *addChannelBefore(struct _Module*, Channel*);
void delChannnel(struct _Module*, Channel*);

#endif /* TRACKER_CHANNEL_H */

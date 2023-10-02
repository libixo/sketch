#ifndef TRACKER_MODULE_H
#define TRACKER_MODULE_H

/* module file definition */
struct _Module;

#define NAME_LEN 20

#include "channel.h"
#include "effect.h"
#include "instrument.h"
#include "pattern.h"

#define ORDER_MAX 256

#define DEFAULT_CHANNELCOUNT 32
#define DEFAULT_BPM 125

typedef struct _Module
{
	char  name  [NAME_LEN+1]; /* module name      */
	char  artist[NAME_LEN+1]; /* artist name      */
	float bpm;                /* beats per minute */
	struct {
		uint8_t global;       /* output volume    */
		uint8_t sample;       /* sample volume    */
	} volume;

	struct {
		bool    state; /* true if a pattern exists, false if it does not */
		uint8_t length;
	} pattern[PATTERN_MAX];

	PatternIndex order[ORDER_MAX];

	ChannelIndex channelcount;
	Channel     *channel;

	Effect     *effect    [EFFECT_MAX];
	Sample     *sample    [SAMPLE_MAX];
	Instrument *instrument[INSTRUMENT_MAX];
} Module;

Module *allocModule(void);
void  freeModule(Module*);

#include "channel.c"
#include "module.c"
#endif /* TRACKER_MODULE_H */

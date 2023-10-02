#ifndef TRACKER_PATTERN_H
#define TRACKER_PATTERN_H

#include "midi.h"
#include "macro.h"
#include "instrument.h"

#define PATTERN_MAX 254
#define PATTERN_VOID 255
#define PATTERN_SEPARATOR 254
typedef uint8_t PatternIndex;
#define PATTERN_LENGTH 256

typedef struct Row
{
	MidiNote        note;
	InstrumentIndex inst;
	Macro           macro[2];
} Row;

typedef struct Pattern
{
	Row row[PATTERN_LENGTH];
} Pattern;

#endif /* TRACKER_PATTERN_H */

#ifndef TRACKER_INSTRUMENT_H
#define TRACKER_INSTRUMENT_H

#include "sample.h"
#include "midi.h"

#define INSTRUMENT_MAX 256
typedef uint8_t InstrumentIndex;

typedef enum Interpolation
{
	InterpolationSampleHold,
	InterpolationLinear,
} Interpolation;

typedef enum NNA
{
	NNANoteCut,
	NNANoteOff,
	NNAContinue,
} NNA;

typedef enum FilterType
{
	FilterOff,
	FilterLowPass,
	FilterHighPass,
} FilterType;

typedef struct _EnvelopePoint
{
	uint8_t x, y;                /* x is relative, y is absolute */
	struct _EnvelopePoint *next; /* linked list, NULL terminated */
} EnvelopePoint;
typedef struct Envelope
{
	uint8_t type;         /* 0 to disable, else type */
	uint8_t loop;         /* point to loop back to, 0 for no loop  */
	uint8_t sustain;      /* point to sustain at, 0 for no sustain */
	EnvelopePoint *point; /* linked list of points                 */
} Envelope;

typedef struct Instrument
{
	char name[NAME_LEN+1];

	/* general */
	uint8_t volume;
	bool    setpanning;
	int8_t  panning;

	/* quality */
	Interpolation interpolation;

	/* filter */
	uint8_t cutoff;
	uint8_t resonance;
	FilterType filtertype;

	/* random variation */
	uint8_t randomvolume;
	uint8_t randompanning;
	uint8_t randomcutoff;
	uint8_t randomresonance;

	/* new note action */
	NNA nna;

	/* sample map */
	SampleIndex sample[MIDI_NOTE_COUNT];

	Envelope volenv;
	Envelope panenv;
	Envelope miscenv;
} Instrument;

Instrument *allocInstrument(InstrumentIndex index);
void                   freeInstrument(Instrument*);

#include "instrument.c"
#endif /* TRACKER_INSTRUMENT_H */

#ifndef TRACKER_INSTRUMENT_C
#define TRACKER_INSTRUMENT_C

Instrument *allocInstrument(InstrumentIndex index)
{
	Instrument *new = calloc(1, sizeof(Instrument));
	memset(&new->sample, index, MIDI_NOTE_COUNT * sizeof(SampleIndex));

	return new;
}

/* safe on NULL */
void freeInstrument(Instrument *i)
{
	free(i);
}

#endif /* TRACKER_INSTRUMENT_C */

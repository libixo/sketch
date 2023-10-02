#ifndef TRACKER_MODULE_C
#define TRACKER_MODULE_C

Module *allocModule(void)
{
	Module *new = calloc(1, sizeof(Module));

	getlogin_r(new->artist, NAME_LEN);
	new->bpm = DEFAULT_BPM;
	new->volume.global = 255;
	new->volume.sample = 127;

	memset(new->order, PATTERN_VOID, ORDER_MAX * sizeof(PatternIndex));

	Channel *lastchannel = NULL;
	for (int i = 0; i < DEFAULT_CHANNELCOUNT; i++)
		lastchannel = addChannelAfter(new, lastchannel);

	return new;
}

void freeModule(Module *m)
{
	/* TODO: free effect */
	for (int i = m->channelcount; i > 0 ; i--)
		delChannel(m, m->channel);

	for (int i = 0; i < SAMPLE_MAX; i++)
		freeSample(m->sample[i]);

	for (int i = 0; i < INSTRUMENT_MAX; i++)
		freeInstrument(m->instrument[i]);

	free(m);
}

#endif /* TRACKER_MODULE_C */

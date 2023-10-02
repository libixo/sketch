#ifndef TRACKER_SAMPLE_C
#define TRACKER_SAMPLE_C

Sample *allocSample(void)
{
	Sample *new = calloc(1, sizeof(Sample));
	new->volume = 255;

	return new;
}

/* safe on NULL */
void freeSample(Sample *s)
{
	if (!s) return;
	free(s->data);
	free(s);
}

#endif /* TRACKER_SAMPLE_C */

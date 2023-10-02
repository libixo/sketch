#ifndef TRACKER_SAMPLE_H
#define TRACKER_SAMPLE_H

#define SAMPLE_MAX 256
typedef uint8_t SampleIndex;

typedef enum LoopType
{
	LoopTypeOff,
	LoopTypeForward,
	LoopTypeBackward,
	LoopTypePingpong,
} LoopType;

typedef struct Sample
{
	char name[NAME_LEN+1];

	uint8_t volume;
	bool setpanning;
	int8_t  panning;

	struct {
		LoopType type;
		uint32_t start;
		uint32_t end;
	} loop;

	struct {
		LoopType type;
		uint32_t start;
		uint32_t end;
	} sustain;

	/* TODO: cue points, cue point 0 is the start of the file */

	uint32_t length;
	uint32_t frequency;
	bool     stereo;
	uint8_t  wordsize; /* 1 for 8bit, 2 for 16bit */
	void    *data;
} Sample;

Sample *allocSample(void);
void  freeSample(Sample*);

#include "sample.c"
#endif /* TRACKER_SAMPLE_H */

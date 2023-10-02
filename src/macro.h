#ifndef TRACKER_MACRO_H
#define TRACKER_MACRO_H

typedef struct Maro
{
	char    command;
	uint8_t value;
} Macro;

typedef struct MacroEntry
{
	void  (*rowcallback)(void);
	void (*proccallback)(void);
} MacroEntry;

MacroEntry macroDescriptor[128] = {
	['c'] /* note cut           */ = {},
	['d'] /* note delay         */ = {},
	['g'] /* gain               */ = {},
	['G'] /* smooth gain        */ = {},
	['+'] /* pitch slide up     */ = {},
	['-'] /* pitch slide down   */ = {},
	['p'] /* pitch slide tone   */ = {},
	['h'] /* vibrato            */ = {},
	['s'] /* pitch shift        */ = {},
	['S'] /* smooth pitch shift */ = {},
	['o'] /* set cue point      */ = {},
	['O'] /* reverse cue point  */ = {},
	['q'] /* retrigger          */ = {},
	['Q'] /* reverse retrigger  */ = {},
};


#endif /* TRACKER_MACRO_H */

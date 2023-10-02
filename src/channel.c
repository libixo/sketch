#ifndef TRACKER_CHANNEL_C
#define TRACKER_CHANNEL_C

void _initChannel(Module *m, Channel *c)
{
	/* allocate any existing patterns */
	for (int i = 0; i < PATTERN_MAX; i++)
		c->pattern[i] = calloc(1, sizeof(Pattern));
}

Channel *addChannelAfter(Module *m, Channel *c)
{
	Channel *new = calloc(1, sizeof(Channel));

	_initChannel(m, new);

	if (c)
	{
		new->next = c->next;
		new->prev = c;
		c->next = new;
	} else /* if no context is given then start a new channel chain */
		m->channel = new;

	m->channelcount++;
	return new;
}
Channel *addChannelBefore(Module *m, Channel *c)
{
	Channel *new = calloc(1, sizeof(Channel));

	_initChannel(m, new);

	if (c)
	{
		new->prev = c->prev;
		new->next = c;
		c->prev = new;
	} else /* if no context is given then start a new channel chain */
		m->channel = new;

	m->channelcount++;
	return new;
}
void delChannel(Module *m, Channel *c)
{
	if (!c) return;
	for (int i = 0; i < PATTERN_MAX; i++)
		if (c->pattern[i])
			free(c->pattern[i]);

	if (c->next) c->next->prev = c->prev;
	if (c->prev) c->prev->next = c->next;
	else /* if there is no previous then c->next is the new first */
		m->channel = c->next;

	m->channelcount--;
	free(c);
}

#endif /* TRACKER_CHANNEL_C */

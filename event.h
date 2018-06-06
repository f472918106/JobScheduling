/* event.h */

#ifndef EVENT
#define EVENT

#include "const.h"

typedef struct Event {
	int time;
	int type;
	int jobid;
	struct Event *prev, *next;
} Eventtype;

Eventtype *createevent(int time, int type);
void destroyevent(Eventtype *event);

void initeventqueue(Eventtype *queue);
void cleareventqueue(Eventtype *queue);
Boolean isemptyeventqueue(Eventtype *queue);
int sizeofeventqueue(Eventtype *queue);

void printevent(Eventtype *e);
void printeventqueue(Eventtype *queue);

Eventtype *firsteventinqueue(Eventtype *queue);
void removeeventfromqueue(Eventtype *event);
void addeventtoqueue(Eventtype *event, Eventtype *queue);
void frontaddeventtoqueue(Eventtype *event, Eventtype *queue);

#endif

/* event.c */

#include <stdio.h>
#include <stdlib.h>
#include "event.h"

Eventtype *createevent(int time, int type)
{
	Eventtype *e;

	if ((e = (Eventtype *) malloc(sizeof(Eventtype))) == NULL)
		return NULL;
	e->time = time, e->type = type, e->jobid = 0;
	e->prev = e->next = e;

	return e;
}

void destroyevent(Eventtype *event)
{
	free(event);
}

void initeventqueue(Eventtype *queue)
{
	queue->prev = queue->next = queue;
}

void cleareventqueue(Eventtype *queue)
{
	Eventtype *e;

	while (isemptyeventqueue(queue) == FALSE) {
		e = firsteventinqueue(queue);
		removeeventfromqueue(e);
		destroyevent(e);
	}
}

Boolean isemptyeventqueue(Eventtype *queue)
{
	if (queue == queue->next)
		return TRUE;
	else
		return FALSE;
}

int sizeofeventqueue(Eventtype *queue)
{
	int n;
	Eventtype *e;

	for (n = 0, e = queue->next; e != queue; ++n, e = e->next)
		;

	return n;
}

void printevent(Eventtype *e)
{
	printf("\n %6d, ", e->time);
	switch (e->type) {
	case JOBCREATEEVENT:
		printf("jobcreate   ");
		break;
	case JOBSCHEDULEEVENT:
		printf("jobschedule ");
		break;
	case JOBEXITEVENT:
		printf("jobexit     ");
		break;
	default:
		printf("unknown event");
	}
	printf(", id=%4d", e->jobid);
		
}

void printeventqueue(Eventtype *queue)
{
	Eventtype *e;

	for (e = queue->next; e != queue; e = e->next) 
		printevent(e);
}

Eventtype *firsteventinqueue(Eventtype *queue)
{
	if (isemptyeventqueue(queue) == TRUE)
		return NULL;
	else
		return queue->next;
}

void removeeventfromqueue(Eventtype *event)
{
	event->prev->next = event->next;
	event->next->prev = event->prev;
	event->prev = event->next = event;
}

void addeventtoqueue(Eventtype *event, Eventtype *queue)
{
	Eventtype *e;

	if (isemptyeventqueue(queue) == TRUE) {
		queue->next = queue->prev = event;
		event->prev = event->next = queue;

		return;
	}

	for (e = queue->next; e != queue && e->time <= event->time; e = e->next)
		;
	event->next = e, event->prev = e->prev;
	e->prev->next = event, e->prev = event;

	return;
}

void frontaddeventtoqueue(Eventtype *event, Eventtype *queue)
{
	Eventtype *e;

	if (isemptyeventqueue(queue) == TRUE) {
		queue->next = queue->prev = event;
		event->prev = event->next = queue;

		return;
	}

	for (e = queue->next; e != queue && e->time < event->time; e = e->next)
		;
	event->next = e, event->prev = e->prev;
	e->prev->next = event, e->prev = event;

	return;
}


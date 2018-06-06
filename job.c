/* job.c */

#include <stdio.h>
#include <stdlib.h>
#include "const.h"
#include "job.h"

Jobtype *createjob(int id, int createtime, int runtime)
{
	Jobtype *job;

	if ((job = (Jobtype *) malloc(sizeof(Jobtype))) == NULL)
		return NULL;

	job->id = id, job->createtime = createtime, job->runtime = runtime;
	job->state = JOBBACKUPSTATE;
	job->turnaroundtime = 0, job->weightedturnaroundtime = 0.0;
	job->prev = job->next = job;

	return job;
}

void destroyjob(Jobtype *job)
{
	free(job);
}

void initjobqueue(Jobtype *queue)
{
	queue->prev = queue->next = queue;
}

void clearjobqueue(Jobtype *queue)
{
	Jobtype *job;

	while (isemptyjobqueue(queue) == FALSE) {
		job = firstjobinqueue(queue);
		removejobfromqueue(job);
		destroyjob(job);
	}
}

Boolean isemptyjobqueue(Jobtype *queue)
{
	if (queue->next == queue)
		return TRUE;
	else 	
		return FALSE;
}

int sizeofjobqueue(Jobtype *queue)
{
	int n;
	Jobtype *job;

	for (n = 0, job = queue->next; job != queue; ++n, job = job->next)
		;
	return n;
}

void printjob(Jobtype *job)
{
	printf("\nid=%2d, create=%4d, ", job->id, job->createtime);
	printf("run=%4d, exit=%4d, ", job->runtime, job->exittime);
	printf("turnad=%4d, ", job->turnaroundtime);
	printf("weightedturnad=%6.2f. ",job->weightedturnaroundtime);
}

void printjobqueue(Jobtype *queue)
{
	Jobtype *job;

	for (job = queue->next; job != queue; job = job->next)
		printjob(job);
}

Jobtype *firstjobinqueue(Jobtype *queue)
{
	if (isemptyjobqueue(queue) == TRUE)
		return NULL;
	else
		return queue->next;
}

Jobtype *shortjobinqueue(Jobtype *queue)
{
	Jobtype *job, *shortjob;


	if (isemptyjobqueue(queue) == TRUE)
		return NULL;
	else {
		for (shortjob = queue->next, job = shortjob->next; 
			job != queue; job = job->next)
			if (job->runtime < shortjob->runtime)
				shortjob = job;
		return shortjob;
	}
}

Jobtype *hrnjobinqueue(Jobtype *queue)
{
	extern int systemtime;
	
	Jobtype *hrnjob, *job;
	double hrn, rn;

	if (isemptyjobqueue(queue) == TRUE)
		return NULL;
	else {
		for (hrnjob = queue->next, job = hrnjob->next;
			 job != queue; job = job->next) {
			hrn = (double) (systemtime - hrnjob->createtime) / 
							hrnjob->runtime;
			rn = (double) (systemtime - job->createtime) / 
							job->runtime;
			if (rn > hrn) 	hrnjob = job;
		}
		return hrnjob;
	}
}

void removejobfromqueue(Jobtype *job)
{
	job->prev->next = job->next;
	job->next->prev = job->prev;
	job->prev = job->next = job;
}

void addjobtoqueue(Jobtype *job, Jobtype *queue)
{
	job->prev = queue->prev;
	job->next = queue;
	queue->prev->next = job;
	queue->prev = job;
}


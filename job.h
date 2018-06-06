/* job.h */

#ifndef JOB
#define JOB

#include "const.h"

typedef struct Job {
	int id;
	int state;
	int createtime;
	int runtime;
	int exittime;

	int turnaroundtime;
	double weightedturnaroundtime;

	struct Job *prev, *next;
} Jobtype;

Jobtype *createjob(int id, int createtime, int runtime);
void destroyjob(Jobtype *job);

void initjobqueue(Jobtype *queue);
void clearjobqueue(Jobtype *queue);
Boolean isemptyjobqueue(Jobtype *queue);
int sizeofjobqueue(Jobtype *queue);

void printjob(Jobtype *job);
void printjobqueue(Jobtype *queue);

Jobtype *firstjobinqueue(Jobtype *queue);
Jobtype *shortjobinqueue(Jobtype *queue);
Jobtype *hrnjobinqueue(Jobtype *queue);

void removejobfromqueue(Jobtype *job);
void addjobtoqueue(Jobtype *job, Jobtype *queue);

#endif






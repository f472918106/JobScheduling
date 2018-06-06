/* jobsch.c */

#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "job.h"
#include "event.h"
#include "handle.h"
#include "cpu.h"

Eventtype eventqueue, exiteventqueue;
Jobtype jobqueue, exitjobqueue;

Cputype cpu;
int systemtime = 0;
int jobid = 1;

int main(int argc, char *argv[])
{

	extern Eventtype eventqueue, exiteventqueue;
	extern Jobtype jobqueue, exitjobqueue;
	extern Cputype cpu;
	extern int systemtime;

	int jobnumber, policy, createtime;
	int turnaroundtime;
	double weightedturnaroundtime;

	int i;
	char *arg2;
	
	Eventtype *e;
	Jobtype *job;
	
	if (argc != 3) {
		printf("\n Please input jobamount!");
		return 1;
	}

	jobnumber = atoi(argv[1]);
	for (arg2 = argv[2]; (*arg2) != '\0'; arg2++)
		(*arg2) = toupper(*arg2);

	if (strcmp(argv[2], "SJF") == 0)
		policy = SJF;
	else if (strcmp(argv[2], "HRN") == 0)
		policy = HRN;
	else
		policy = FCFS;

	initeventqueue(&eventqueue);
	initeventqueue(&exiteventqueue);

	initjobqueue(&jobqueue);
	initjobqueue(&exitjobqueue);

	initcpu(&cpu, policy);
	
	createtime = 0;
	for (i = 0; i < jobnumber; ++i) {
		createtime += NEXTJOBCREATETIMEINTERVAL;
		e = createevent(createtime, JOBCREATEEVENT);
		addeventtoqueue(e, &eventqueue);
	}


	while (isemptyeventqueue(&eventqueue) == FALSE) {
		e = firsteventinqueue(&eventqueue);
		removeeventfromqueue(e);
		systemtime = e->time;

		switch (e->type) {
		case JOBCREATEEVENT:
			jobcreateeventhandle(e);
			break;
		case JOBSCHEDULEEVENT:
			jobscheduleeventhandle(e);
			break;
		case JOBEXITEVENT:
			jobexiteventhandle(e);
			break;
		default:
			break;
		}
		addeventtoqueue(e, &exiteventqueue);
	}

	printf("\nEVETNQUEUE:");
	printeventqueue(&exiteventqueue);

		
	printf("\nJOBQUEUE:");
	printjobqueue(&exitjobqueue);

	for (turnaroundtime = 0, weightedturnaroundtime = 0.0, 
		job = firstjobinqueue(&exitjobqueue);
		job != &exitjobqueue; job = job->next) {
		turnaroundtime += job->turnaroundtime;
		weightedturnaroundtime += job->weightedturnaroundtime;
	}
	cpu.turnaroundtime = turnaroundtime / cpu.jobnumber;
	cpu.weightedturnaroundtime = weightedturnaroundtime / cpu.jobnumber;

	printf("\nCPU:");
	cpu.freetime = systemtime - cpu.busytime;
	printcpu(&cpu);

	printf("\n");

	cleareventqueue(&eventqueue);
	cleareventqueue(&exiteventqueue);
	clearjobqueue(&jobqueue);
	clearjobqueue(&exitjobqueue);

	return 0;
}
